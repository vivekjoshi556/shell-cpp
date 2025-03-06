#include <cstdlib>
#include "exit.hpp"

namespace commands {
    void ExitCommand::execute() {
        std::exit(0);
    }
}