#include "cd.hpp"
#include <cstring>
#include <cstdlib>
#include <errno.h>
#include <unistd.h>
#include <iostream>

namespace cmds {
    void CdCommand::execute() {
        std::string path = args[0];
        if (path[0] == '~') {
            path = getenv("HOME") + path.substr(1);
        }
        if (chdir(path.c_str()) == -1) {
            std::cout << name << ": " << path.c_str() << ": " << strerror(errno) << std::endl;
        }
    }
}