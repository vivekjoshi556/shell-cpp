#include <string>
#include <csignal>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include "core/command.hpp"
#include "core/exitException.hpp"
#include "utils/commandUtils.hpp"
#include "core/commandFactory.hpp"
#include "core/commandRegistry.hpp"
#include "core/terminalSettings.hpp"

int main() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::string input;

    TerminalSettings &instance = TerminalSettings::getInstance();

    while(true) {
        std::cout << "$ ";
        input.clear();

        input = cmds::getCommand();

        if (input.empty())
            continue;

        history.push_back(input);
        std::vector<cmds::CommandPtr> commands = cmds::createCommand(input);
        int prev_pipe_read = -1;
        std::vector<pid_t> pids;

        // Single Command Exectuion
        if (commands.size() == 1) {
            auto &command = commands[0];
            if (command) {
                try {
                    command->execute();
                } catch (const ExitException& e) {
                    // Exit Exception to exit program and let the call stack unroll.
                    break;
                }
            }

            continue;
        }

        // Pipelined Execution
        pid_t pgid = 0;
        for (size_t i = 0; i < commands.size(); i++) {
            auto &command = commands[i];
            int pipefd[2];
            
            if(i < commands.size() - 1) {
                pipe(pipefd);
            }

            int input_fd = (prev_pipe_read == -1 ? STDIN_FILENO: prev_pipe_read);
            int output_fd = (i == commands.size() - 1 ? STDOUT_FILENO : pipefd[1]);

            pid_t pid = commands[i]->piped_execute(input_fd, output_fd, i == 0 ? 0 : pgid);

            // If this is the first process of pipeline use it to decide the pgid.
            if (i == 0) {
                pgid = pid;
                setpgid(pid, pgid);
                // give control of terminal to the children pgroup
                tcsetpgrp(STDIN_FILENO, pgid);
                // restore default signla behavior
                signal(SIGINT, SIG_DFL);
            }

            pids.push_back(pid);

            if (prev_pipe_read != -1)
                close(prev_pipe_read);
            if (i < commands.size() - 1) {
                close(pipefd[1]);
                prev_pipe_read = pipefd[0];
            }
        }

        // Wait processes from pipelined Execution:
        for (pid_t pid: pids) {
            waitpid(pid, nullptr, 0);
        }
        instance.applyRawMode();
    }

    return 0;
}
