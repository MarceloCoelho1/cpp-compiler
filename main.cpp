#include <iostream>
#include <string>
#include <vector>
#include <regex>

int main() {
    std::regex LETTERS("[a-zA-Z]");
    std::string text = "marcelo";
    
    std::vector<char> code(text.begin(), text.end());

    while (!code.empty()) {
        std::string t("");
        while (!code.empty() && std::regex_match(std::string(1, code.front()), LETTERS)) {
            t += code.front();
            code.erase(code.begin());
        }
        if (!t.empty()) {
            std::cout << t << std::endl;
        }
    }

    return 0;
}

