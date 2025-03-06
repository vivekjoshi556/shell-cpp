#include "command.hpp"
#include "../utils/commandUtils.hpp"

namespace commands {
    Command::Command(
        const std::string &name, const std::string &args, const CommandType type, const std::string &path
    ) {
        this->name = name;
        this->type = type;
        this->args = parseCommands(args);
        this->exec_path = path;
    }
}