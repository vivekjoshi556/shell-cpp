#ifndef TYPE_COMMAND_HPP
#define TYPE_COMMAND_HPP

#include "../command.hpp"

namespace cmds {
    class TypeCommand: public Command {
    public:
        using Command::Command;
        void execute() override;
    };
}

#endif