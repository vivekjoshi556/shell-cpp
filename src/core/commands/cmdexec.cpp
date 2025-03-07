#include <unistd.h>
#include <iostream>
#include <filesystem>
#include <sys/wait.h>
#include "cmdexec.hpp"

namespace cmds {
    void Cmdexec::execute() {
        if(access(exec_path.c_str(), X_OK) != 0) {
            std::cout << exec_path << ": Permission denied" << std::endl;
            return;
        }

        pid_t child_pid = fork();

        if (child_pid == 0) {
            // const char* argv[3];
            std::vector<const char*> argv;
            
            argv.push_back(std::filesystem::path(exec_path).filename().c_str());

            for(const auto &arg: args) {
                argv.push_back(arg.c_str());
            }

            argv.push_back(nullptr);
            
            execv(exec_path.c_str(), const_cast<char* const*>(argv.data()));
        }

        // Handle failures.

        wait(NULL);
    }
}