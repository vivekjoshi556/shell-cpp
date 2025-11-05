#include <cstdlib>
#include "../exitException.hpp"
#include "exit.hpp"

namespace cmds {
    void ExitCommand::execute() {
        throw ExitException();
    }
}