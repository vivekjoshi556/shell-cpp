#ifndef COMMAND_REGISTRY_HPP
#define COMMAND_REGISTRY_HPP

#include <string>
#include "command.hpp"
#include <unordered_map>

namespace commands {
    template <typename T>
    CommandPtr makeCommand(
        const std::string &name,
        const std::string &args,
        const CommandType type,
        const std::string &path
    ) {
        return std::make_unique<T>(name, args, type, path);
    }

    extern const std::unordered_map<std::string, CommandCreator> command_registry;
}

#endif 