#include <iostream>
#include "echo.hpp"

namespace commands {
    void EchoCommand::execute() {
        std::cout << args << std::endl;
    }
}