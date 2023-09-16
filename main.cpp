#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "Tokens.h"
#include "TokenType.h" 

int main() {
    std::regex LETTERS("[a-zA-Z]");
    std::string text = "name 10.1";
    std::regex NUMBERS("[0-9]");
    
    std::vector<char> code(text.begin(), text.end());
    std::vector<Tokens> tokens;
    while (!code.empty()) {
        if(code.front() == '"') {
            code.erase(code.begin());
            std::string text("");
            while(!code.empty() && std::regex_match(std::string(1, code.front()), LETTERS) || !code.empty() && code.front() == ' ') {
                text += code.front();
                code.erase(code.begin());
            }
            code.erase(code.begin());
            Tokens token(TEXT, text);
            tokens.push_back(token);
            std::cout << "String: " << text << std::endl;
        }
        if(std::regex_match(std::string(1, code.front()), LETTERS)) {
            std::string text("");
            while(!code.empty() && std::regex_match(std::string(1, code.front()), LETTERS)) {
                text += code.front();
                code.erase(code.begin());
            }
            Tokens token(ID, text);
            tokens.push_back(token);

            std::cout << "Identifier: " << text << std::endl;
        }
        if(code.front() == '\n' || code.front() == ' ') {
            code.erase(code.begin());
            continue;
        }
        if(std::regex_match(std::string(1, code.front()), NUMBERS)) {
            std::string number("");
            int flag = 0;
            while(!code.empty() && std::regex_match(std::string(1, code.front()), NUMBERS) || !code.empty() && code.front() == '.') {
                if(code.front() == '.') {
                    flag = 1;
                }
                number += code.front();
                code.erase(code.begin());
            }

            if(flag == 1) {
                Tokens token(NUM_DEC, number);
                tokens.push_back(token);
            } else {
                Tokens token(NUM_INT, number);
                tokens.push_back(token);
            }
            
            std::cout << "Number: " << number << std::endl;
        }
    }

    for (int i = 0; i < tokens.size(); i++) {
        std::cout << "Tipo: " << tokens[i].getType() << ", Valor: " << tokens[i].getValue() << std::endl;
    }

    return 0;
}
