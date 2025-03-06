#ifndef TYPES_HPP
#define TYPES_HPP

#include <memory>

namespace commands {
    // Forward declaration.
    class Command;

    // Types
    enum class CommandType {
        BUILTIN,
        PATH,
        DIRECT,
        UNKNOWN
    };

    using CommandPtr = std::unique_ptr<Command>;
    using CommandCreator = CommandPtr (*)(const std::string&, const std::string&, const CommandType, const std::string&);
    
}

#endif