#include <unistd.h>
#include "terminalSettings.hpp"

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
}

TerminalSettings::~TerminalSettings() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
}
