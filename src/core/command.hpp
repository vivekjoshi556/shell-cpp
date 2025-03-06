#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <vector>
#include "../utils/types.hpp"

namespace commands {
    class Command {
    protected:
        std::string name;
        std::vector<std::string> args;
        CommandType type;
        std::string exec_path;

    public:
        explicit Command(const std::string&, const std::string&, const CommandType, const std::string&);
        virtual void execute() = 0;
        virtual ~Command() = default;
    };
}

#endif