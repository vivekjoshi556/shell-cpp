#ifndef TERMINAL_SETTINGS_HPP
#define TERMINAL_SETTINGS_HPP

#include <termios.h>

class TerminalSettings {
public:
    static TerminalSettings& getInstance();
    struct termios& getOriginal();

private:
    TerminalSettings();
    ~TerminalSettings();

    TerminalSettings(const TerminalSettings&) = delete;
    TerminalSettings& operator=(const TerminalSettings&) = delete;

    struct termios original;
};

#endif
