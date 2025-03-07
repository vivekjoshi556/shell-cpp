#ifndef PWD_COMMAND_HPP
#define PWD_COMMAND_HPP

#include "../command.hpp"

namespace cmds {
    class PwdCommand: public Command {
    public:
        using Command::Command;
        void execute() override;
    };
}

#endif