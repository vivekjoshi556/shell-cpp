#ifndef TERMINAL_SETTINGS_HPP
#define TERMINAL_SETTINGS_HPP

#include <atomic>
#include <vector>
#include <string>
#include <termios.h>

extern std::atomic<bool> interrupted;
extern std::vector<std::string> history;

class TerminalSettings {
public:
    static TerminalSettings& getInstance();
    struct termios& getOriginal();
    void applyRawMode();

private:
    TerminalSettings();
    ~TerminalSettings();

    // Disable copy construction and copy assignment to prevent accidental copying of TerminalSettings instances.
    TerminalSettings(const TerminalSettings&) = delete;
    TerminalSettings& operator=(const TerminalSettings&) = delete;

    struct termios original;
};

#endif
