#ifndef HISTORY_COMMAND_HPP
#define HISTORY_COMMAND_HPP

#include "../command.hpp"

namespace cmds {
    class HistoryCommand: public Command {
        static int appendIdx;
    public:
        using Command::Command;
        void execute() override;
        static void readHistoryFile(std::string);
        static void writeHistoryFile(std::string);
        static void appendHistoryFile(std::string);
    };
}

#endif