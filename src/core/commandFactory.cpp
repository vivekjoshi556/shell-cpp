#include <iostream>

#include "commandFactory.hpp"
#include "commandRegistry.hpp"
#include "../utils/commandUtils.hpp"

namespace cmds {
    CommandPtr createCommand(const std::string &command) {
        std::vector<std::string> resp = parseCommands(command);

        std::string name = resp[0];
        resp.erase(resp.begin());

        std::pair<CommandType, std::string> cmd_type = findCommandType(name);

        if(cmd_type.first == CommandType::BUILTIN) {
            auto it = command_registry.find(name);
            return it->second(name, resp, cmd_type.first, cmd_type.second);
        } 
        else if(cmd_type.first == CommandType::PATH || cmd_type.first == CommandType::DIRECT) {
            auto it = command_registry.find("cmdexec");
            return it->second(name, resp, cmd_type.first, cmd_type.second);
        }
        else if(cmd_type.first == CommandType::UNKNOWN) {
            std::cout << name << ": command not found" << std::endl;
        }
    
        return nullptr;
    }
}