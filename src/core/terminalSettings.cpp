#include <atomic>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include "commands/history.hpp"
#include "terminalSettings.hpp"

std::atomic<bool> interrupted = false;
std::vector<std::string> history;

using namespace cmds;

TerminalSettings& TerminalSettings::getInstance() {
    static TerminalSettings instance;
    return instance;
}

struct termios& TerminalSettings::getOriginal() {
    return original;
}

void sigint_handler(int signo) {
    std::cout << std::endl << "$ ";
    interrupted = true;
}

void TerminalSettings::applyRawMode() {
    struct termios raw = original;
    
    // disable canonical mode & echo so input gets processed 1 char at a time.
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    
    signal(SIGINT, sigint_handler);
}

TerminalSettings::TerminalSettings() {
    tcgetattr(STDIN_FILENO, &original);
    applyRawMode();
    
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