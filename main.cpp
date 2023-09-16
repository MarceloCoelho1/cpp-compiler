#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "Tokens.h"
#include "TokenType.h" 
#include <unordered_map>

int main() {
    std::string text = "return";
    std::regex LETTERS("[a-zA-Z]");
    std::regex NUMBERS("[0-9]");

     std::unordered_map<std::string, std::string> map;

        // Reserved keywords in Python
        map["and"] = "and";
        map["as"] = "as";
        map["assert"] = "assert";
        map["async"] = "async";
        map["await"] = "await";
        map["break"] = "break";
        map["class"] = "class";
        map["continue"] = "continue";
        map["def"] = "def";
        map["del"] = "del";
        map["elif"] = "elif";
        map["else"] = "else";
        map["except"] = "except";
        map["False"] = "False";
        map["finally"] = "finally";
        map["for"] = "for";
        map["from"] = "from";
        map["global"] = "global";
        map["if"] = "if";
        map["import"] = "import";
        map["in"] = "in";
        map["is"] = "is";
        map["lambda"] = "lambda";
        map["None"] = "None";
        map["not"] = "not";
        map["or"] = "or";
        map["return"] = "return";

   
    
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

            auto it = map.find(text);

            if(it != map.end()) {
                Tokens token(RESERVED_KEYWORD, text);
                tokens.push_back(token);
            } else {
                Tokens token(ID, text);
                tokens.push_back(token);
            }
            
            

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
        if(code.front() == '/' && code.at(1) == '/') {
            code.erase(code.begin());
            code.erase(code.begin());
            if(code.front() == ' ') {
                code.erase(code.begin());
            }

            std::string comment("");
            while(!code.empty() && code.front() != '\n') {
                comment += code.front();
                code.erase(code.begin());
            }

            Tokens token(COMMENT, comment);
            tokens.push_back(token);
        }
    }

    for (int i = 0; i < tokens.size(); i++) {
        std::cout << "Tipo: " << tokens[i].getType() << ", Valor: " << tokens[i].getValue() << std::endl;
    }

    return 0;
}

std::string text(std::vector<char> code) {
    std::string text = "";
    int check = 0;

    if(code.empty()) return ""; // if code is empty return an empty string

    for(auto &x : code) { // run through code checking if has an text start with
                          // checking the double aspas and end with it
        if(x == '\"') check == 0 ? check = 1 : check = 0;
        // need to add the simple aspas and the double ones

        if(check == 1) {
            text+=x; // if check is ok, add the text to the string as it is written
        }
    }
    return text; // return the text written
}
