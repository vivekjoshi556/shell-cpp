#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <vector>
#include <unistd.h>
#include "../utils/types.hpp"

namespace cmds {
    class Command {
    protected:
        std::string name;
        std::vector<std::string> args;
        CommandType type;
        std::string exec_path;

    public:
        explicit Command(const std::string&, std::vector<std::string>&, const CommandType, const std::string&);
        virtual void execute() = 0;

        /**
         * Expects the `read` end of pipe of previous process.
         * Returns the `read` end of the pipe it will write to.
         */
        pid_t piped_execute(int input_fd = STDIN_FILENO, int output_fd = STDOUT_FILENO, pid_t pgid = 0);
        virtual ~Command();
        std::string getName();
        CommandType getType();
        void addArg(std::string);
    };
}

#endif