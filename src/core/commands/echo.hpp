#ifndef ECHO_COMMAND_HPP
#define ECHO_COMMAND_HPP

#include "../command.hpp"

namespace commands {
    class EchoCommand: public Command {
    public:
        using Command::Command;
        void execute() override;
    };
}

#endif