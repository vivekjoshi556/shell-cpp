#include <unistd.h>
#include <iostream>
#include "commandUtils.hpp"
#include "../core/commandRegistry.hpp"

namespace commands {
    std::pair<CommandType, std::string> findCommandType(const std::string &name) {
        int start, end = -1;
        std::string s = std::getenv("PATH");
        char del = ':';
        
        if(commands::command_registry.find(name) != commands::command_registry.end()) {
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
}