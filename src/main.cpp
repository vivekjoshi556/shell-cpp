#include <iostream>
#include "core/command.hpp"
#include "core/commandFactory.hpp"

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string input;
  while(true) {
    std::cout << "$ ";
    std::getline(std::cin, input);

    if (input == "")
      continue;

    auto command = commands::createCommand(input);
    if (command) {
      command->execute();
    }
   }
}
