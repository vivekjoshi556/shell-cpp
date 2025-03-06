#ifndef COMMAND_FACTORY_HPP
#define COMMAND_FACTORY_HPP

#include "command.hpp"

namespace commands {
    CommandPtr createCommand(const std::string&);
}

#endif