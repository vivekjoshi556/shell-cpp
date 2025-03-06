#include "type.hpp"
#include <iostream>
#include "../../utils/commandUtils.hpp"

namespace commands {

    void TypeCommand::execute() {

        std::pair<CommandType, std::string> type = findCommandType(args);

        switch (type.first) {
            case CommandType::BUILTIN:
                std::cout << args << " is a shell builtin\a" << std::endl;
                break;
            case CommandType::PATH:
                std::cout << args << " is " << type.second << std::endl;
                break;
            case CommandType::UNKNOWN:
                std::cout << args << ": not found" << std::endl;
        }
    }
}