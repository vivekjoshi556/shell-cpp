#include <cstdlib>
#include "exit.hpp"

namespace cmds {
    void ExitCommand::execute() {
        std::exit(0);
    }
}