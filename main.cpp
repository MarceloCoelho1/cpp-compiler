#include <iostream>
#include <string>
#include <vector>
#include <regex>

int main() {
    std::regex LETTERS("[a-zA-Z]");
    std::string text = "name";
    std::regex NUMBERS("[0-9]");

    std::vector<char> code(text.begin(), text.end());


    while (!code.empty()) {
        if(code.front() == '"') {
            code.erase(code.begin());
            std::string text("");
            while(!code.empty() && std::regex_match(std::string(1, code.front()), LETTERS) || !code.empty() && code.front() == ' ') {
                text += code.front();
                code.erase(code.begin());
            }
            code.erase(code.begin());


            std::cout << "String: " << text << std::endl;
        }
        if(std::regex_match(std::string(1, code.front()), LETTERS)) {
            std::string text("");
            while(!code.empty() && std::regex_match(std::string(1, code.front()), LETTERS)) {
                text += code.front();
                code.erase(code.begin());
            }


            std::cout << "Identifier: " << text << std::endl;
        }
        if(code.front() == '\n' || code.front() == ' ') {
            code.erase(code.begin());
            continue;
        }
        if(std::regex_match(std::string(1, code.front()), NUMBERS)) {
            std::string number("");
            while(!code.empty() && std::regex_match(std::string(1, code.front()), NUMBERS) || !code.empty() && code.front() == '.') {
                number += code.front();
                code.erase(code.begin());
            }
            std::cout << number << std::endl;
        }
    }

    return 0;
}

