#include <iostream>

#include "commandFactory.hpp"
#include "commandRegistry.hpp"
#include "../utils/commandUtils.hpp"

namespace cmds {
    CommandPtr createCommand(const std::string &command) {
        size_t index = command.find(" ");
        std::string name = parseCommands(command.substr(0, index))[0];
        std::string args = (index == std::string::npos) ? "" : command.substr(command.find(" ") + 1);

        std::pair<CommandType, std::string> cmd_type = findCommandType(name);

        if(cmd_type.first == CommandType::BUILTIN) {
            auto it = command_registry.find(name);
            return it->second(name, args, cmd_type.first, cmd_type.second);
        } 
        else if(cmd_type.first == CommandType::PATH || cmd_type.first == CommandType::DIRECT) {
            auto it = command_registry.find("cmdexec");
            return it->second(name, args, cmd_type.first, cmd_type.second);
        }
        else if(cmd_type.first == CommandType::UNKNOWN) {
            std::cout << name << ": command not found" << std::endl;
        }
    
        return nullptr;
    }
}