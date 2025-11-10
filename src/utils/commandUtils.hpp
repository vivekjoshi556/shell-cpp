#ifndef COMMAND_UTILS_HPP
#define COMMAND_UTILS_HPP

#include <vector>
#include <iostream>
#include "types.hpp"

namespace cmds {
    extern int std_out;
    extern int std_err;

    std::pair<CommandType, std::string> findCommandType(const std::string&);
    std::pair<std::vector<std::string>, int> parseCommands(const std::string&, int);

    std::vector<std::string> autoComplete(const std::string &);
    std::string getCommand();
}

#endif