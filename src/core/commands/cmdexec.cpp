#include <iostream>
#include <unistd.h>
#include <filesystem>
#include <sys/wait.h>
#include "cmdexec.hpp"

namespace fs = std::filesystem;

namespace cmds {
    void Cmdexec::execute() {
        pid_t pid = this->piped_execute();
        if (pid != -1) {
            waitpid(pid, nullptr, 0);
        }
    }

    pid_t Cmdexec::piped_execute(int input_fd, int output_fd, int pgid) {
        if(access(exec_path.c_str(), X_OK) != 0) {
            std::cout << exec_path << ": Permission denied" << std::endl;
            return -1;
        }

        pid_t pid = fork();

        if (pid == 0) {
            if (input_fd != STDIN_FILENO) {
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }
            if (output_fd != STDOUT_FILENO) {
                dup2(output_fd, STDOUT_FILENO);
                close(output_fd);
            }
            
            setpgid(pid, pgid);
            signal(SIGINT, SIG_DFL);

            std::vector<const char*> argv;
            
            argv.push_back(fs::path(exec_path).filename().c_str());

            for(const auto &arg: args) {
                argv.push_back(arg.c_str());
            }

            argv.push_back(nullptr);
            
            execv(exec_path.c_str(), const_cast<char* const*>(argv.data()));
        }

        return pid;
    }
}