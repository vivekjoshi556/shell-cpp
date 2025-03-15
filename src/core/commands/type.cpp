#include "type.hpp"
#include <iostream>
#include "../../utils/commandUtils.hpp"

namespace cmds {
    void TypeCommand::execute() {

        for (const auto &arg: args) {
            std::pair<CommandType, std::string> type = findCommandType(arg);

            switch (type.first) {
                case CommandType::BUILTIN:
                    std::cout << arg << " is a shell builtin\a" << std::endl;
                    break;
                case CommandType::PATH:
                    std::cout << arg << " is " << type.second << std::endl;
                    break;
                case CommandType::UNKNOWN:
                    std::cout << arg << ": not found" << std::endl;
            }
        }
    }
}