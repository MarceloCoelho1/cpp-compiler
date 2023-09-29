#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "Tokens.h"
#include "TokenType.h"
#include <unordered_map>

// global declarations
int currentIndentLevel = 0;

std::vector<Tokens> tokens;
std::regex LETTERS("[a-zA-Z]");
std::regex NUMBERS("[0-9]");
std::regex ARITMETICOPERATIONS("[+\\-*/%]");
std::regex SYMBOLS("[,],{,}");
std::regex COMPARISON_SYMBOLS("==,<=,>=,>,<,||,&&,!=,?,:");

bool isReservedKeyword(std::string word, std::string text)
{
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
    map["print"] = "print";
    map["return"] = "return";
    map["while"] = "while";

    auto it = map.find(text);

    if (it != map.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void tokenizer(std::string input)
{
    std::vector<char> code(input.begin(), input.end());
    while (!code.empty())
    {
        if (code.front() == '"')
        {
            code.erase(code.begin());
            std::string text("");
            while (!code.empty() && std::regex_match(std::string(1, code.front()), LETTERS) || !code.empty() && code.front() == ' ')
            {
                text += code.front();
                code.erase(code.begin());
            }
            code.erase(code.begin());
            Tokens token(STRING, text);
            tokens.push_back(token);
            std::cout << "String: " << text << std::endl;
            continue;
        }
        if (code.front() == '(')
        {
            std::string symbol("(");
            Tokens token(OPEN_PAREN, symbol);
            tokens.push_back(token);
            code.erase(code.begin());
            continue;
        }
        if (code.front() == ')')
        {
            std::string symbol(")");
            Tokens token(CLOSE_PAREN, symbol);
            tokens.push_back(token);
            code.erase(code.begin());
            continue;
        }
        if (std::regex_match(std::string(1, code.front()), SYMBOLS))
        {
            std::string symbol(1, code.front());
            Tokens token(SYMBOL, symbol);
            tokens.push_back(token);
            code.erase(code.begin());
            continue;
        }
        if (code.front() == ':')
        {
            std::string symbol(":");
            Tokens token(CODEBLOCK, symbol);
            tokens.push_back(token);
            code.erase(code.begin());
            continue;
        }
        if (code.front() == '=')
        {

            std::string symbol("=");
            Tokens token(EQUALS, symbol);
            tokens.push_back(token);
            code.erase(code.begin());
            continue;
        }
        if (std::regex_match(std::string(1, code.front()), LETTERS))
        {
            std::string text("");
            while (!code.empty() && std::regex_match(std::string(1, code.front()), LETTERS))
            {
                text += code.front();
                code.erase(code.begin());
            }

            bool isReserved = isReservedKeyword(text, input);
            if (isReserved)
            {
                Tokens token(RESERVED_KEYWORD, text);
                tokens.push_back(token);
            }
            else
            {
                Tokens token(ID, text);
                tokens.push_back(token);
            }

            continue;
        }
        if (code.front() == ' ' || code.front() == '\t')
        {
            code.erase(code.begin());
            continue;
        }

        if (code.front() == '\n')
        {
            code.erase(code.begin());
            int newIndentLevel = 0;
            while (!code.empty() && (code.front() == ' ' || code.front() == '\t'))
            {
                newIndentLevel++;
                code.erase(code.begin());
            }
            if (newIndentLevel < currentIndentLevel)
            {

                Tokens token(ENDCODEBLOCK, "endBlockCode");
                tokens.push_back(token);
            }
            currentIndentLevel = newIndentLevel;
            continue;
        }
        if (std::regex_match(std::string(1, code.front()), NUMBERS))
        {
            std::string number("");
            int flag = 0;
            while (!code.empty() && std::regex_match(std::string(1, code.front()), NUMBERS) || !code.empty() && code.front() == '.')
            {
                if (code.front() == '.')
                {
                    flag = 1;
                }
                number += code.front();
                code.erase(code.begin());
            }

            if (flag == 1)
            {
                Tokens token(NUM_DEC, number);
                tokens.push_back(token);
            }
            else
            {
                Tokens token(NUM_INT, number);
                tokens.push_back(token);
            }

            continue;
        }
        if (code.front() == '/' && code.at(1) == '/')
        {
            code.erase(code.begin());
            code.erase(code.begin());
            if (code.front() == ' ')
            {
                code.erase(code.begin());
            }

            std::string comment("");
            while (!code.empty() && code.front() != '\n')
            {
                comment += code.front();
                code.erase(code.begin());
            }

            Tokens token(COMMENT, comment);
            tokens.push_back(token);
            continue;
        }
        if (code.front() == ';')
        {

            std::string symbol(";");
            Tokens token(SEMICOLON, symbol);
            tokens.push_back(token);
            code.erase(code.begin());
            continue;
        }
        if (std::regex_match(std::string(1, code.front()), ARITMETICOPERATIONS))
        {
            std::string symbol("");
            while (!code.empty() && std::regex_match(std::string(1, code.front()), ARITMETICOPERATIONS))
            {
                symbol += code.front();
                code.erase(code.begin());
            }
            Tokens token(BINARY_OPERATOR, symbol);
            tokens.push_back(token);
            continue;
        }
        std::cout << "Error: " << code.front() << std::endl;
        break;
    }
}

std::string getFileContent(std::string url)
{
    std::ifstream myfile;
    std::string buffer;
    myfile.open(url);
    if (myfile.is_open())
    {
        std::string myline;
        while (std::getline(myfile, myline))
        {
            buffer += myline + '\n';
        }
    }

    return buffer;
}

int main()
{

    std::string buffer = getFileContent("./inputCode/main.py");
    tokenizer(buffer);

    for (int i = 0; i < tokens.size(); i++)
    {
        std::cout << "Tipo: " << tokens[i].getType() << ", Valor: " << tokens[i].getValue() << std::endl;
    }

    return 0;
}
