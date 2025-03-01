#include <iostream>
#include "type.hpp"
#include "../commandFactory.hpp"

namespace commands {
    void TypeCommand::execute() {
        if(commands::command_registry.find(args) != commands::command_registry.end()) {
            std::cout << args << " is a shell builtin" << std::endl;
        } 
        else {
            std::cout << args << ": not found" << std::endl;
        }
    }
}