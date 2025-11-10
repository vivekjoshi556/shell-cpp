#ifndef COMMAND_FACTORY_HPP
#define COMMAND_FACTORY_HPP

#include "command.hpp"

namespace cmds {
    std::vector<CommandPtr> createCommand(const std::string&);
}

#endif