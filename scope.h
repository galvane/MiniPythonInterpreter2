//
// Created by osboxes on 11/21/18.
//

#ifndef ORDONEZ_HW4_SCOPE_H
#define ORDONEZ_HW4_SCOPE_H

#endif //ORDONEZ_HW4_SCOPE_H

#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Scope{
public:
    string name;
    string type;
    map<string,string> variables;
    vector<string> parameters;
    string conditionalStatement;
    string returnStatement;

    Scope(string name, string type);
    void addVariable(string name, string value);
    void addParameter(string parameter);
    Scope getTail();
};
