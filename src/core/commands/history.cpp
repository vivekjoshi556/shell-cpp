#include <iostream>
#include "history.hpp"
#include <fstream>
#include <filesystem>
#include <unordered_map>
#include "../terminalSettings.hpp"

namespace fs = std::filesystem;

namespace cmds {
    int HistoryCommand::appendIdx = 0;

    void HistoryCommand::execute() {
        int length = history.size();
        std::unordered_map<std::string, std::string> config = {
            {"-r", ""}, {"-w", ""}, {"-n", ""}, {"-a", ""}
        };

        for (int i = 0; i < args.size(); i++) {
            if (config.find(args[i]) != config.end()) {
                if ((i + 1) < args.size()) {
                    config[args[i]] = args[i + 1];
                }
                i += 1;
            }
            else {
                config["-n"] = args[i];
            }
        }

        // Read
        if (config["-r"] != "") {
            // Does not raise any error for now.
            readHistoryFile(config["-r"]);
            return;
        }

        // Write
        if (config["-w"] != "") {
            writeHistoryFile(config["-w"]);
            return;
        }

        // Append
        if (config["-a"] != "") {
            appendHistoryFile(config["-a"]);
            return;
        }

        // Output Size
        if (config["-n"] != "") {
            try {
                length = std::stoi(config["-n"]);
                if (length < 0) {
                    length = history.size();
                } else if (length > history.size()) {
                    length = history.size();
                }
            } catch (...) {
                std::cout << "Invalid argument for history: " << config["-n"] << std::endl;
                length = history.size();
            }
        }

        for (int i = history.size() - length; i < history.size(); i++) {
            std::cout << i + 1 << "  " << history[i] << std::endl;
        }
    }

    void HistoryCommand::readHistoryFile(std::string filename) {
        if (access(filename.c_str(), R_OK) == 0) {
            std::ifstream infile(filename);
            if (!infile) {
                std::cerr << "Failed to open file" << std::endl;
            }

            std::string line;
            while (std::getline(infile, line)) {
                if (line != "") {
                    history.push_back(line);
                }
            }

            appendIdx = history.size();

            infile.close();

        }
        return;
    }

    void HistoryCommand::writeHistoryFile(std::string filename) {
        if (fs::exists(filename) && access(filename.c_str(), W_OK) != 0) {
            return;
        }

        std::ofstream outfile(filename);
        if (!outfile) {
            std::cerr << "Failed to open file" << std::endl;
        }
        for(int i = 0; i < history.size(); i++) {
            outfile << history[i] << std::endl;
        }
        return;
    }

    void HistoryCommand::appendHistoryFile(std::string filename) {
        if (!fs::exists(filename) || access(filename.c_str(), W_OK) != 0) {
            return;
        }

        std::ofstream outfile(filename.c_str(), std::ios::app);
        if (!outfile) {
            std::cerr << "Failed to open file" << std::endl;
        }
        for(int i = appendIdx; i < history.size(); i++) {
            outfile << history[i] << std::endl;
        }
        appendIdx = history.size();
        return;
    }
}