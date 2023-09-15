#include <iostream>
#include <string>
#include <vector>
#include <regex>

int main() {
    std::regex LETTERS("[a-zA-Z]");
    std::string text = "marcelo\n Henrique\n Brito\n Coelho\n";
    
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
    }

    return 0;
}

