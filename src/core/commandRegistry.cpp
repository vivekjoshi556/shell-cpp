#include "commandRegistry.hpp"

#include "./commands/cd.hpp"
#include "./commands/pwd.hpp"
#include "./commands/exit.hpp"
#include "./commands/type.hpp"
#include "./commands/echo.hpp"
#include "./commands/history.hpp"
#include "./commands/cmdexec.hpp"

namespace cmds {
    const std::unordered_map<std::string, CommandCreator> command_registry = {
        {"cd", makeCommand<CdCommand>},
        {"pwd", makeCommand<PwdCommand>},
        {"echo", makeCommand<EchoCommand>},
        {"history", makeCommand<HistoryCommand>},
        {"type", makeCommand<TypeCommand>},
        {"exit", makeCommand<ExitCommand>},
        {"cmdexec", makeCommand<Cmdexec>}
    };
}