//
// Created by osboxes on 11/17/18.
//

#ifndef ORDONEZ_HW4_MAIN_H
#define ORDONEZ_HW4_MAIN_H


#endif //ORDONEZ_HW4_MAIN_H

#include <iostream>
#include <vector>
#include <map>
#include "scope.h"

using namespace std;

class Main {
public:
    static Scope *globalScope;
    static map<string, string>globalVariables;

    static string do_arithmetic(vector<string>);

    static string performAssignment(int, Scope *, int);
};

bool check_if(int, Scope*);
int else_index;
bool isfunctioncallAssignment(int);
