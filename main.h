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
    static map<Token, Token>globalVariables;
    bool operator< (const Token& tokenObj) const;

    Token(int line, string type, string content, int level);
    static void updateTokens(Token token);
    static void createTokenObjs(vector<string> flexInput);
};

class Scope{
public:
    string name;
    string type;
    map<string,int> variables;
    vector<string> parameters;

    Scope(string name, string type);
    void addVariable(string name, int value);
    void addParameter(string parameter);
};


/* Node of a doubly linked list */
struct Node {
    Scope *data;
    struct Node* next;
    struct Node* prev;
};
