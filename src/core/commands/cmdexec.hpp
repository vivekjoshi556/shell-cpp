#ifndef CMD_EXEC_COMMAND_HPP
#define CMD_EXEC_COMMAND_HPP

#include "../command.hpp"

namespace commands {
    class Cmdexec: public Command {
    public:
        using Command::Command;
        void execute() override;
    };
}

#endif 