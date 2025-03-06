#include "pwd.hpp"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

namespace commands {
    void PwdCommand::execute() {
        std::cout << fs::current_path().c_str() << std::endl;
    }
}