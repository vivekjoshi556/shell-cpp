#include <iostream>
#include <fcntl.h>
#include "command.hpp"
#include <unordered_set>
#include "../utils/commandUtils.hpp"

namespace cmds {
    Command::Command(
        const std::string &name, const std::string &args, const CommandType type, const std::string &path
    ) {
        this->name = name;
        this->type = type;
        this->exec_path = path;
        
        std::vector<std::string> tokens = parseCommands(args);
        std::unordered_set<std::string> redirects = {">", "1>", "2>", ">>", "1>>", "2>>"};

        int i = 0;
        
        for(; i < tokens.size(); i++) {
            std::string &arg = tokens[i];
            if (redirects.find(arg) != redirects.end()) {
                break;
            }
            this->args.push_back(tokens[i]);
        }

        for (; i < tokens.size(); i++) {
            std::string &arg = tokens[i];
            if (arg == ">" || arg  == "1>" || arg == ">>" || arg  == "1>>") {
                int flags = O_CREAT | O_WRONLY | ((arg.find(">>") == std::string::npos) ? O_TRUNC : O_APPEND);
                int fp = open(tokens[i + 1].c_str(), flags, 0644);
                dup2(fp, STDOUT_FILENO);
                close(fp);
            }
            if (arg == "2>") {
                int flags = O_CREAT | O_WRONLY | ((arg.find(">>") == std::string::npos) ? O_TRUNC : O_APPEND);
                int fp = open(tokens[i + 1].c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
                dup2(fp, STDERR_FILENO);
                close(fp);
            }
        }
    }

    std::string Command::getName() { 
        return this->name;
    }

    Command::~Command() {
        // Clean up for 
        dup2(std_out, STDOUT_FILENO);
        dup2(std_err, STDERR_FILENO);
    }
}