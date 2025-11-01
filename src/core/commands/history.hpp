#ifndef HISTORY_COMMAND_HPP
#define HISTORY_COMMAND_HPP

#include "../command.hpp"

namespace cmds {
    class HistoryCommand: public Command {
    public:
        using Command::Command;
        void execute() override;
    };
}

#endif