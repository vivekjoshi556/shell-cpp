#include <unistd.h>
#include "commands/history.hpp"
#include "terminalSettings.hpp"

std::vector<std::string> history;
using namespace cmds;

TerminalSettings& TerminalSettings::getInstance() {
    static TerminalSettings instance;
    return instance;
}

struct termios& TerminalSettings::getOriginal() {
    return original;
}

TerminalSettings::TerminalSettings() {
    tcgetattr(STDIN_FILENO, &original);

    struct termios raw = original;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    // Env Varibles Setup
    if (getenv("HISTFILE") != nullptr) {
        cmds::HistoryCommand::readHistoryFile(getenv("HISTFILE"));
    }
}

TerminalSettings::~TerminalSettings() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);

    if (getenv("HISTFILE") != nullptr) {
        cmds::HistoryCommand::writeHistoryFile(getenv("HISTFILE"));
    }
}
