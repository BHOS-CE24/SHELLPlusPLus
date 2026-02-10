#include "tokenizer.h"
#include "builtins.h"
#include <iostream>
#include <vector>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>

int main() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::string command;

    while (true) {
        std::cout << "$ ";
        std::getline(std::cin, command);
        if (command.empty()) continue;

        auto args = tokenise(command);
        if (args.empty()) continue;

        if (handle_builtin(args)) continue;

        pid_t pid = fork();
        if (pid == 0) {
            std::vector<char*> cargs;
            for (auto& arg : args) cargs.push_back(arg.data());
            cargs.push_back(nullptr);
            execvp(cargs[0], cargs.data());
            std::cout << args[0] << ": command not found\n";
            std::exit(1);
        } else if (pid > 0) {
            waitpid(pid, nullptr, 0);
        } else {
            perror("fork failed");
        }
    }

    return 0;
}
