#include <iostream>
#include <string>
#include <vector>
#include <regex>

int main() {
    std::regex LETTERS("[a-zA-Z]");
    std::string text = "120";
    std::regex NUMBERS("[0-9]");

    std::vector<char> code(text.begin(), text.end());


    while (!code.empty()) {
        if(std::regex_match(std::string(1, code.front()), LETTERS)) {
            std::string t("");
            while(!code.empty() && std::regex_match(std::string(1, code.front()), LETTERS)) {
                t += code.front();
                code.erase(code.begin());
            }
            std::cout << t << std::endl;
        }
        if(code.front() == '\n' || code.front() == ' ') {
            code.erase(code.begin());
            continue;
        }
        if(std::regex_match(std::string(1, code.front()), NUMBERS)) {
            std::string number("");
            while(!code.empty() && std::regex_match(std::string(1, code.front()), NUMBERS)) {
                number += code.front();
                code.erase(code.begin());
            }
            std::cout << number << std::endl;
        }
    }

    return 0;
}

