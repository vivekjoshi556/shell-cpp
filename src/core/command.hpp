#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "../utils/types.hpp"

namespace commands {
    class Command {
    protected:
        std::string name, args;
        CommandType type;
        std::string exec_path;

    public:
        explicit Command(const std::string &name, const std::string &args, const CommandType type, const std::string &path): name(name), args(args), type(type), exec_path(path) {}
        virtual void execute() = 0;
        virtual ~Command() = default;
    };
}

#endif