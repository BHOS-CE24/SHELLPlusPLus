#include "tokenizer.h"
#include <cctype>

std::vector<std::string> tokenise(const std::string& line) {
    std::vector<std::string> tokens;
    std::string current;
    bool in_single_quote = false;
    bool in_double_quote = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];

        if (!in_single_quote && c == '\\' && i + 1 < line.size()) {
            current += line[i + 1];
            ++i;
            continue;
        }

        if (c == '\'' && !in_double_quote) {
            in_single_quote = !in_single_quote;
            continue;
        }

        if (c == '\"' && !in_single_quote) {
            in_double_quote = !in_double_quote;
            continue;
        }

        if (!in_single_quote && !in_double_quote && isspace(c)) {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
        } else {
            current += c;
        }
    }

    if (!current.empty()) tokens.push_back(current);

    return tokens;
}

// # Author: Vugar Ahadli (Vuq17)
// # Date: 2026-02-11