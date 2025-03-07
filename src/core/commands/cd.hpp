#ifndef CD_COMMAND_HPP
#define CD_COMMAND_HPP

#include "../command.hpp"

namespace cmds {
    class CdCommand: public Command {
    public:
        using Command::Command;
        void execute() override;
    };
}

#endif