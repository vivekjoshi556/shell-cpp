#include <iostream>
#include "echo.hpp"

namespace cmds {
    void EchoCommand::execute() {
        for (const std::string &str: args)
            std::cout << str << " ";
        std::cout << std::endl;
    }
}