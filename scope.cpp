//
// Created by osboxes on 11/21/18.
//

#include "scope.h"

Scope::Scope(string name, string type){
    this->name = name;
    this->type = type;
}
void Scope::addVariable(string name, string value){
    this->variables.insert(pair<string, string>(name, value));
}
void Scope::addParameter(string parameter){
    this->parameters.push_back(parameter);
}
