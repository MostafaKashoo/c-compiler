#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

unordered_set<string> keywords = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
    "else", "enum", "extern", "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof", "static", "struct",
    "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

bool isKeyword(const string& word) {
    return keywords.find(word) != keywords.end();
}

bool isSpecialSymbol(char ch) {
    string special = "();{}[],";
    return special.find(ch) != string::npos;
}

bool isOperator(char ch) {
    string ops = "+-*/%=<>!";
    return ops.find(ch) != string::npos;
}

int main() {
    string code;
    cout << "Enter C code below (end with # on a new line):\n";
    string line;
    while (getline(cin, line)) {
        if (line == "#") break;
        code += line + '\n';
    }

    cout << "\nTOKENS:\n\n";

    string token;
    for (size_t i = 0; i < code.size(); ++i) {
        char ch = code[i];
        if (isspace(ch)) continue;
        if (isalpha(ch) || ch == '_') {
            token.clear();
            while (isalnum(code[i]) || code[i] == '_') {
                token += code[i++];
            }
            --i;
            if (isKeyword(token))
                cout << "Keyword\t\t" << token << "\n";
            else
                cout << "Identifier\t" << token << "\n";
        }
        else if (isdigit(ch)) {
            token.clear();
            while (isdigit(code[i])) {
                token += code[i++];
            }
            --i;
            cout << "Number\t\t" << token << "\n";
        }
        else if (isOperator(ch)) {
            token.clear();
            token += ch;
            if (i + 1 < code.size()) {
                string two = token + code[i + 1];
                if (two == "==" || two == "!=" || two == "<=" || two == ">=" || two == "++" || two == "--") {
                    token = two;
                    i++;
                }
            }
            cout << "Operator\t" << token << "\n";
        }
        else if (isSpecialSymbol(ch)) {
            cout << "Special Symbol\t" << ch << "\n";
        }
        else if (ch == '/' && i + 1 < code.size() && code[i + 1] == '/') {
            while (i < code.size() && code[i] != '\n') i++;
        }
        else if (ch == '/' && i + 1 < code.size() && code[i + 1] == '*') {
            i += 2;
            while (i + 1 < code.size() && !(code[i] == '*' && code[i + 1] == '/')) i++;
            i++;
        }
    }

    return 0;
}
