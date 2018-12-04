//
// Created by osboxes on 11/21/18.
//


#ifndef ORDONEZ_HW4_SCOPE_H
#define ORDONEZ_HW4_SCOPE_H


#include <iostream>
#include <vector>
#include <map>
#include "token.h"

using namespace std;

class Scope{
public:
    int lexer_line;
    int line;
    int level;
    string name;
    string type;
    Token *token;
    map<string,string> variables;
    vector<string> parameters;
    string conditionalStatement;
    string returnStatement;
    string elseStatement;
    string printStatement;
    static bool mutation;

    Scope(string name, string type);
    void addVariable(string name, string value);
    void addParameter(string parameter);
    Scope getTail();
};

#endif //ORDONEZ_HW4_SCOPE_H