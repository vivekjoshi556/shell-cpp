#ifndef CMD_EXEC_COMMAND_HPP
#define CMD_EXEC_COMMAND_HPP

#include "../command.hpp"

namespace cmds {
    class Cmdexec: public Command {
    public:
        using Command::Command;
        void execute() override;
        pid_t piped_execute(int input_fd = STDIN_FILENO, int output_fd = STDOUT_FILENO, int pgid = 0);
    };
}

#endif 