#include <cstdlib>
#include "type.hpp"
#include <unistd.h>
#include <iostream>
#include <filesystem>
#include "../commandFactory.hpp"

namespace fs = std::filesystem;

namespace commands {

    void TypeCommand::execute() {
        int start, end = -1;
        std::string s = std::getenv("PATH");
        char del = ':';
        
        do {
            start = end + 1;
            end = s.find(del, start);
            std::string path_url = s.substr(start, end - start) + "/" + args;

            if (access(path_url.c_str(), F_OK) == 0 && access(path_url.c_str(), X_OK) == 0) {
                std::cout << args << " is " << path_url << std::endl;
                return;
            }
        } while (end != -1);

        if(commands::command_registry.find(args) != commands::command_registry.end()) {
            std::cout << args << " is a shell builtin" << std::endl;
        } 
        else {
            std::cout << args << ": not found" << std::endl;
        }
    }
}