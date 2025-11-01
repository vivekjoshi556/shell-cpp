#include <string>
#include <unistd.h>
#include <iostream>
#include "core/command.hpp"
#include "utils/commandUtils.hpp"
#include "core/commandFactory.hpp"
#include "core/commandRegistry.hpp"
#include "core/terminalSettings.hpp"

int main() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::string input;

    TerminalSettings &instance = TerminalSettings::getInstance();

    while(true) {
        std::cout << "$ ";
        input.clear();

        input = cmds::getCommand();

        if (input.empty())
            continue;

        history.push_back(input);
        auto command = cmds::createCommand(input);
        if (command) {
            command->execute();
        }
    }

    return 0;
}
