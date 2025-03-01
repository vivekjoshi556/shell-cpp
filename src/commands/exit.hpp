#ifndef EXIT_COMMAND_HPP
#define EXIT_COMMAND_HPP

#include "command.hpp"

namespace commands {
    class ExitCommand: public Command {
    public:
        using Command::Command;
        void execute() override;
    };
}

#endif 