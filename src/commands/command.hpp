#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <memory>

namespace commands {
    class Command {
    protected:
        std::string name, args;

    public:
        explicit Command(const std::string &name, const std::string &args): name(name), args(args) {}
        virtual void execute() = 0;
        virtual ~Command() = default;
    };
}

#endif