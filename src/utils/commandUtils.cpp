#include <unistd.h>
#include <iostream>
#include "commandUtils.hpp"
#include "../core/commandRegistry.hpp"

namespace cmds {
    std::pair<CommandType, std::string> findCommandType(const std::string &name) {
        int start, end = -1;
        std::string s = std::getenv("PATH");
        char del = ':';
        
        if(command_registry.find(name) != command_registry.end()) {
            return std::make_pair(CommandType::BUILTIN, "");
        } 

        do {
            start = end + 1;
            end = s.find(del, start);
            std::string path_url = s.substr(start, end - start) + "/" + name;

            if (access(path_url.c_str(), F_OK) == 0 && access(path_url.c_str(), X_OK) == 0) {
                return std::make_pair(CommandType::PATH, path_url);
            }
        } while (end != -1);

        return std::make_pair(CommandType::UNKNOWN, "");
    }

    std::vector<std::string> parseCommands(const std::string &str) {
        std::vector<std::string> result;
        
        if(str.empty()) return result;

        std::string token;
    
        for (char ch : str) {
            if (ch == ' ') {
                if (!token.empty()) {
                    result.push_back(token);
                    token.clear();
                }
            } else {
                token += ch;
            }
        }
    
        if (!token.empty()) {
            result.push_back(token);
        }
    
        return result;
    }
}