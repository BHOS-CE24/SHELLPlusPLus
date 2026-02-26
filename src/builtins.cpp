#include "builtins.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

bool handle_builtin(const std::vector<std::string>& args) {
    if (args.empty()) return false;

    if (args[0] == "exit") std::exit(0);

    if (args[0] == "echo") {
        for (size_t i = 1; i < args.size(); ++i) {
            std::cout << args[i];
            if (i + 1 < args.size()) std::cout << " ";
        }
        std::cout << "\n";
        return true;
    }

    if (args[0] == "pwd") {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd))) std::cout << cwd << "\n";
        else perror("pwd failed");
        return true;
    }

    if (args[0] == "cd") {
        if (args.size() < 2) {
            std::cerr << "cd: missing argument\n";
        } else {
            std::string path = args[1];
            if (!path.empty() && path[0] == '~') {
                const char* home = getenv("HOME");
                if (home) path = std::string(home) + path.substr(1);
            }
            if (chdir(path.c_str()) != 0) {
                std::cerr << "cd: " << path << ": " << strerror(errno) << "\n";
            }
        }
        return true;
    }

    if (args[0] == "type") {
        if (args.size() < 2) {
            std::cout << "type: missing argument\n";
            return true;
        }

        std::string name = args[1];
        std::vector<std::string> builtins{"exit", "echo", "type", "pwd", "cd"};

        for (const auto& b : builtins) {
            if (b == name) {
                std::cout << name << " is a shell builtin\n";
                return true;
            }
        }

        const char* path_env = getenv("PATH");
        bool found_external = false;
        if (path_env) {
            std::stringstream ss(path_env);
            std::string dir;
            while (std::getline(ss, dir, ':')) {
                if (dir.empty()) continue;
                std::string full_path = dir + "/" + name;
                if (access(full_path.c_str(), X_OK) == 0) {
                    std::cout << name << " is " << full_path << "\n";
                    found_external = true;
                    break;
                }
            }
        }

        if (!found_external) std::cout << name << ": not found\n";
        return true;
    }

    return false;
}

// # Author: Vugar Ahadli (Vuq17)
// # Date: 2026-02-11