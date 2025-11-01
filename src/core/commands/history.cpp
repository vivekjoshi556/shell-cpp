#include <iostream>
#include "history.hpp"
#include "../terminalSettings.hpp"

namespace cmds {
    void HistoryCommand::execute() {
        int length = history.size();
        if (args.size() == 1) {
            try {
                length = std::stoi(args[0]);
                if (length < 0) {
                    length = history.size();
                } else if (length > history.size()) {
                    length = history.size();
                }
            } catch (...) {
                std::cout << "Invalid argument for history: " << args[0] << std::endl;
                length = history.size();
            }
        }
        for (int i = history.size() - length; i < history.size(); i++) {
            std::cout << i + 1 << "  " << history[i] << std::endl;
        }
    }
}