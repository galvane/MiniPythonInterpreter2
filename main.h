//
// Created by osboxes on 11/17/18.
//

#ifndef ORDONEZ_HW4_MAIN_H
#define ORDONEZ_HW4_MAIN_H


#endif //ORDONEZ_HW4_MAIN_H

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Token {
public:
    int line;
    string type;
    string content;
    int level; //level of indent
    static vector<Token>tokens;
    static map<Token, Token>variables;
    bool operator< (const Token& tokenObj) const;

    Token(int line, string type, string content, int level);
    static void updateTokens(Token token);
    static void createTokenObjs(vector<string> flexInput);
};
