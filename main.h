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
    static int i;
    static bool if_result;
    static int if_level;
    static bool inside_function;
    static bool last_line;
    static Scope *globalScope;
    static map<string, string>globalVariables;
    static map<string, int>functions;
    static bool check_if(int, Scope*);
    static int scope_engine(int i, Scope *scope);

    Main(Scope *globalScope);

    static string do_arithmetic(vector<string>);

    static string performAssignment(int, Scope *, int);
    static void print(int, Scope*);
};


int else_index;
bool isfunctioncallAssignment(int);

