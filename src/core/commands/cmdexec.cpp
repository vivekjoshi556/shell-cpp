#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include "cmdexec.hpp"

namespace commands {
    void Cmdexec::execute() {
        pid_t child_pid = fork();

        if (child_pid == 0) {
            const char* argv[3];
            argv[0] = exec_path.c_str();

            if (!args.empty()) {
                argv[1] = args.c_str();
                argv[2] = nullptr;
            } else {
                argv[1] = nullptr;
            }
            
            execv(exec_path.c_str(), const_cast<char* const*>(argv));
        }

        // Handle failures.

        wait(NULL);
    }
}