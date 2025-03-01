#include <iostream>

#include "./commands/exit.hpp"
#include "./commands/type.hpp"
#include "./commands/echo.hpp"
#include "commandFactory.hpp"

namespace commands {
    const std::unordered_map<std::string, CommandConstructor> command_registry = {
        {"echo", createCommand<EchoCommand>},
        {"type", createCommand<TypeCommand>},
        {"exit", createCommand<ExitCommand>}
    };

    CommandPtr createCommand(const std::string &command) {
        size_t index = command.find(" ");
        std::string name = command.substr(0, index);
        std::string args = (index == std::string::npos) ? "" : command.substr(command.find(" ") + 1);

        auto it = command_registry.find(name);
        if(it == command_registry.end()) {
            std::cout << name << ": command not found" << std::endl;
            return nullptr;
        }

        return it->second(name, args);
    }
}