#include <fcntl.h>
#include <csignal>
#include "command.hpp"
#include <unordered_set>
#include "../utils/commandUtils.hpp"

namespace cmds {
    Command::Command(
        const std::string &name, std::vector<std::string> &tokens, const CommandType type, const std::string &path
    ) {
        this->name = name;
        this->type = type;
        this->exec_path = path;

        std::unordered_set<std::string> redirects = {">", "1>", "2>", ">>", "1>>", "2>>"};

        int i = 0;
        
        for(; i < tokens.size(); i++) {
            std::string &arg = tokens[i];
            if (redirects.find(arg) != redirects.end()) {
                break;
            }
            this->args.push_back(tokens[i]);
        }

        for (; i < tokens.size(); i++) {
            std::string &arg = tokens[i];
            if (arg == ">" || arg  == "1>" || arg == ">>" || arg  == "1>>") {
                int flags = O_CREAT | O_WRONLY | ((arg.find(">>") == std::string::npos) ? O_TRUNC : O_APPEND);
                int fp = open(tokens[i + 1].c_str(), flags, 0644);
                dup2(fp, STDOUT_FILENO);
                close(fp);
            }
            if (arg == "2>" || arg == "2>>") {
                int flags = O_CREAT | O_WRONLY | ((arg.find(">>") == std::string::npos) ? O_TRUNC : O_APPEND);
                int fp = open(tokens[i + 1].c_str(), flags, 0644);
                dup2(fp, STDERR_FILENO);
                close(fp);
            }
        }
    }

    std::string Command::getName() { 
        return this->name;
    }

    cmds::CommandType Command::getType() { 
        return this->type;
    }

    void Command::addArg(std::string arg) {
        this->args.push_back(arg);
    }

    pid_t Command::piped_execute(int input_fd, int output_fd, pid_t pgid) {
        pid_t pid = fork();
        if (pid == 0) {
            if (input_fd != STDIN_FILENO) {
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }
            if (output_fd != STDOUT_FILENO) {
                dup2(output_fd, STDOUT_FILENO);
                close(output_fd);
            }
            
            setpgid(pid, pgid);
            signal(SIGINT, SIG_DFL);
            
            this->execute();
            exit(0);
        }

        return pid;
    }

    Command::~Command() {
        // Clean up for 
        dup2(std_out, STDOUT_FILENO);
        dup2(std_err, STDERR_FILENO);
    }
}