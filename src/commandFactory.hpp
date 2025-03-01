#ifndef COMMAND_FACTORY_HPP
#define COMMAND_FACTORY_HPP

#include <unordered_map>
#include "./commands/command.hpp"

namespace commands {
    using CommandPtr = std::unique_ptr<Command>;

    template <typename T>
    CommandPtr createCommand(const std::string &name, const std::string &args) {
        return std::make_unique<T>(name, args);
    }

    using CommandConstructor = CommandPtr (*)(const std::string&, const std::string&);

    extern const std::unordered_map<std::string, CommandConstructor> command_registry;

    CommandPtr createCommand(const std::string&);
}

#endif