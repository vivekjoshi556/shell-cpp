#include <iostream>
#include "echo.hpp"

namespace commands {
    void EchoCommand::execute() {
        for (const std::string &str: args)
            std::cout << str << " ";
        std::cout << std::endl;
    }
}