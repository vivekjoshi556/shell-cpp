#include "commandRegistry.hpp"
#include "../utils/commandUtils.hpp"

namespace cmds {
    std::vector<CommandPtr> createCommand(const std::string &command) {
        std::vector<CommandPtr> result;
        int at = 0;
        while(at < command.size()) {
            std::pair<std::vector<std::string>, int> commands = parseCommands(command, at);
            at = commands.second + 1;

            std::vector<std::string> &resp = commands.first;
            std::string name = resp[0];
            resp.erase(resp.begin());

            std::pair<CommandType, std::string> cmd_type = findCommandType(name);

            if(cmd_type.first == CommandType::BUILTIN) {
                auto it = command_registry.find(name);
                result.push_back(it->second(name, resp, cmd_type.first, cmd_type.second));
            } 
            else if(cmd_type.first == CommandType::PATH || cmd_type.first == CommandType::DIRECT) {
                auto it = command_registry.find("cmdexec");
                result.push_back(it->second(name, resp, cmd_type.first, cmd_type.second));
            }
            else if(cmd_type.first == CommandType::UNKNOWN) {
                std::cout << name << ": command not found" << std::endl;
                result.clear();
                return result;
            }
        }
    
        return result;
    }
}
