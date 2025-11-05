#include <algorithm>
#include <filesystem>
#include <unordered_set>
#include "commandUtils.hpp"
#include "../core/commandRegistry.hpp"
#include "../core/terminalSettings.hpp"

namespace fs = std::filesystem;

namespace cmds {
    // stdout and stderr duplicates used during redirection.
    int std_out = dup(STDOUT_FILENO);
    int std_err = dup(STDERR_FILENO);

    void cleanup() {
        close(std_out);
        close(std_err);
    }

    static bool registered = [] {
        atexit(cleanup);
        return true;
    }();

    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        if (strs.empty()) return "";

        std::sort(strs.begin(), strs.end());
        std::string first = strs[0];
        std::string last = strs[strs.size() - 1];
        int i = 0;

        while (i < first.size() && i < last.size() && first[i] == last[i]) {
            i++;
        }
    
        return first.substr(0, i);
    }    

    std::pair<CommandType, std::string> findCommandType(const std::string &name) {
        int start, end = -1;
        std::string s = std::getenv("PATH");
        char del = ':';
        
        if (command_registry.find(name) != command_registry.end()) {
            return std::make_pair(CommandType::BUILTIN, "");
        }

        if (access(name.c_str(), F_OK) == 0) {
            return std::make_pair(CommandType::DIRECT, name);
        }

        do {
            start = end + 1;
            end = s.find(del, start);
            std::string path_url = s.substr(start, end - start) + "/" + name;

            if (access(path_url.c_str(), F_OK | X_OK) == 0) {
                return std::make_pair(CommandType::PATH, path_url);
            }
        } while (end != -1);

        return std::make_pair(CommandType::UNKNOWN, "");
    }

    std::vector<std::string> parseCommands(const std::string &str) {
        std::vector<std::string> result;
        
        if (str.empty()) return result;

        std::string token;
        bool activeSingleQuote = false;
        bool activeDoubleQuote = false;
        bool escape = false;
    
        for (char ch : str) {
            if (activeSingleQuote || activeDoubleQuote) {
                if (activeSingleQuote && ch != '\'') {
                    token.push_back(ch);
                }
                else if (activeDoubleQuote && (ch != '"' || (escape && ch == '"'))) {
                    if (!escape && ch == '\\') {
                        escape = true;
                        continue;
                    }
                    if (escape) {
                        escape = false;
                        if (ch != '\\' && ch != '$' && ch != '"') {
                            token.push_back('\\');
                        }
                    }
                    token.push_back(ch);
                }
                else if (activeSingleQuote) {
                    activeSingleQuote = false;
                }
                else if (activeDoubleQuote) {
                    activeDoubleQuote = false;
                }
                continue;
            }

            if (escape) {
                escape = false;
                token.push_back(ch);
                continue;
            }

            if (ch == '\'') {
                activeSingleQuote = true;
            }
            else if (ch == '"') {
                activeDoubleQuote = true;
            }
            else if (ch == '\\') {
                escape = true;
            }
            else if (ch == ' ') {
                if (!token.empty()) {
                    result.push_back(token);
                    token.clear();
                }
            }
            else {
                token.push_back(ch);
            }
        }
    
        if (!token.empty()) {
            result.push_back(token);
        }
    
        return result;
    }

    std::vector<std::string> autoComplete(const std::string &partial) {
        std::vector<std::string> result;

        if (partial == "") 
            return result;

        std::unordered_set<std::string> names_found;
        
        // Look into built-in commands
        for(auto it: command_registry) {
            if(it.first.find(partial) == 0) {
                result.push_back(it.first);
                names_found.insert(it.first);
            }
        }

        // Look into path
        std::string env = getenv("PATH");
        int start = 0, end = 0;
        std::string dir_path = "";
        std::unordered_set<std::string> processed_paths;

        while (start < env.size()) {
            end = env.find(':', start);
            if(end != std::string::npos) {
                dir_path = env.substr(start, end - start);
                start = end + 1;
            }
            else {
                if(start < env.size()) {
                    dir_path = env.substr(start);
                }
                start = env.size();
            }

            if (dir_path != "" && processed_paths.find(dir_path) == processed_paths.end()) {
                processed_paths.insert(dir_path);

                // Resolve HOME
                if (dir_path[0] == '~') {
                    dir_path = getenv("HOME") + dir_path.substr(1);
                }

                if (!fs::exists(dir_path) || !fs::is_directory(dir_path)) {
                    continue;
                }

                for (auto const &dir_entry: fs::directory_iterator(dir_path)) {
                    std::string p = dir_entry.path().string();

                    int last_idx = p.find_last_of(fs::path::preferred_separator);
                    if (last_idx != std::string::npos) {
                        p = p.substr(last_idx + 1);
                        
                        if(p.find(partial) == 0) {
                            if (names_found.find(p) == names_found.end())
                                result.push_back(p);
                        }
                    }
                }
                dir_path = "";
            }
        }

        return result;
    }

    std::string getCommand() {
        char ch;
        bool firstTab = true;
        std::string result;
        std::vector<std::string> completions;
        std::string currCommand = "";
        int historyIdx = history.size();

        while (true) {
            read(STDIN_FILENO, &ch, 1);

            if (ch == '\n') {
                // What if there is an open quote or other similar scenarios.
                std::cout << std::endl;
                break;
            }
            else if (ch == 27) {
                read(STDIN_FILENO, &ch, 1);
                if (ch == '[') {
                    read(STDIN_FILENO, &ch, 1);
                    if (ch == 'A') { // up arrow key
                        if (historyIdx == history.size()) {
                            currCommand = result;
                        }
                        if (historyIdx == 0)
                            continue;
                        historyIdx -= 1;
                    
                        result = history[historyIdx];
                    }
                    else if (ch == 'B') { // down arrow key
                        if (historyIdx == history.size()) {
                            continue;
                        }
                        historyIdx += 1;

                        result = (historyIdx == history.size()) ? currCommand : history[historyIdx];
                    }
                    std::cout<< "\33[2K\r" << "$ " << result;
                }
            }
            else if (ch == 127 || ch == '\b') {
                if (!result.empty()) {
                    result.pop_back();
                    std::cout << "\b \b";
                }
            }
            else if (ch == '\t') {
                if (firstTab) {
                    completions = autoComplete(result);
                    if (completions.size() == 1) {
                        std::cout << completions[0].substr(result.size()) << " ";
                        result = completions[0] + " ";
                    }
                    else if (completions.size() > 1) {
                        std::string prefix = longestCommonPrefix(completions);
                        if (prefix.size() > 0)
                            firstTab = false;

                        std::cout << prefix.substr(result.size());
                        result += prefix.substr(result.size());
                        std::cout << "\a";
                    }
                    else if (completions.size() == 0) {
                        std::cout << "\a";
                    }
                }
                else {
                    std::cout << std::endl;
                    for (std::string &str: completions) {
                        std::cout << str << "  ";
                    }
                    std::cout << std::endl << "$ " << result;
                }
            }
            else if (isprint(ch)) {
                result += ch;
                std::cout << ch;
            }

            if (!firstTab && ch != '\t') {
                firstTab = true;
            }
        }

        return result;
    }

}