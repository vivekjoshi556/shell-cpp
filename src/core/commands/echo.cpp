#include <iostream>
#include "echo.hpp"

namespace cmds {
    void EchoCommand::execute() {
        for (int i = 0; i < args.size(); i++) {
            std::cout << args[i];
            if (i < args.size() - 1)
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}