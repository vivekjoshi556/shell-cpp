#ifndef COMMAND_UTILS_HPP
#define COMMAND_UTILS_HPP

#include <string>
#include "types.hpp"

namespace commands {
    std::pair<CommandType, std::string> findCommandType(const std::string&);
}

#endif