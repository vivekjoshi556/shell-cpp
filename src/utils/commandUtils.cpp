#include <unistd.h>
#include <iostream>
#include "commandUtils.hpp"
#include "../core/commandRegistry.hpp"

namespace cmds {
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

            if (access(path_url.c_str(), F_OK) == 0) {
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
}