#include <iostream>
#include <string>
#include <vector>
#include <regex>

int main() {
    std::regex LETTERS("[a-zA-Z]");
    std::string text = "120.10";
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
            while(!code.empty() && std::regex_match(std::string(1, code.front()), NUMBERS) || !code.empty() && code.front() == '.') {
                number += code.front();
                code.erase(code.begin());
            }
            std::cout << number << std::endl;
        }
    }

    return 0;
}

std::string text(std::vector<char> code) {
    std::string text = "";
    int check = 0;

    if(code.empty()) return ""; // if code is empty return an empty string

    for(auto &x : code) { // run through code checking if has an text start with
                          // checking the double aspas(or simple one) and end with it
        if(code == '\"' || code == '\'') check < 1 ? check++ : check--;
        // need to add the simple aspas and the double ones

        if(check == 1) {
            text+=x; // if check is ok, add the text to the string as it is written
        }
    }
    return text; // return the text written
}
