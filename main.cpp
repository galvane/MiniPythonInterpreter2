#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <vector>
#include <map>
#include <cmath>
#include <cstdio>
#include <set>
#include <algorithm>
#include "main.h"

using namespace std;

// split function
vector<string> split(string str, string delimiter){
    vector<string> parameters;
    size_t pos = 0;
    string token;
    while ((pos = str.find(delimiter)) != string::npos) {
        token = str.substr(0, pos);
        str.erase(0, pos + delimiter.length());
        parameters.push_back(token);
    }
    return parameters;
}

// DOUBLY LINKED LIST INSERTION:
void appendToDLL(struct Node ** head, Scope *newData) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    struct Node* last = *head;

    newNode->data = newData;

    newNode->next = NULL;

    if (*head == NULL)
    {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = newNode;

    newNode->prev = last;

    return;
}

vector<Token>Token::tokens;
map<Token, Token>Token::globalVariables;
// pointers to function scope blocks
vector<Node*>functionScopes;

//constructor
Token::Token(int line, string type, string content, int level){
    this->line = line;
    this->type = type;
    this->content = content;
    this->level = level;
}
//overloading operator <
bool Token::operator< (const Token& tokenObj) const
{
    if(tokenObj.line < this->line)
        return true;
}

//update/set tokens
void Token::updateTokens(Token token){
    tokens.push_back(token);
}

vector<string> getFlexInput(){
    ifstream ifs;
    ifs.open("output.txt");

    if (!ifs) {
        cout << "Unable to open file";
        exit(1);
    }

    string line; //temp var
    vector<string> input;

    while(ifs){
        getline(ifs, line);
        input.push_back(line);
    }
    line.clear();
    ifs.close();
    return input;
}

//create Token objects with associated attributes
void Token::createTokenObjs(vector<string> flexInput){
    for(int i = 0; i < flexInput.size(); i++){
        if(flexInput.at(i) != "\n" && flexInput.at(i).size() != 0) {

            string current = flexInput.at(i);
            int lineIndex = current.find("LINE=");
            int typeIndex = current.find("TYPE=");
            int contentIndex = current.find("TOKEN=");
            int levelIndex = current.find("LEVEL=");

            try {
                int line = stoi(current.substr(lineIndex + 5, typeIndex - lineIndex - 5 - 1));
                string type = current.substr(typeIndex + 5, contentIndex - typeIndex - 5-1);
                string content = current.substr(contentIndex+6,levelIndex-contentIndex-6-1);
                int level= stoi(current.substr(levelIndex+6, current.size() - levelIndex-1));

                Token *token = new Token(line, type, content, level);
                Token::updateTokens(*token);
            }catch(const invalid_argument& ia){
                cerr << "Invalid argument: " << ia.what() << '\n';
            }
        }
    }
}

void recognizeScopes(){
    for(int i = 0; i < Token::tokens.size(); i++){
        if(Token::tokens.at(i).type == "KEYWORD" || Token::tokens.at(i).type == "FUNCTION"){

        }
    }
}

bool isVariableAssignment(int i){
    return (Token::tokens.at(i).type == ("VARIABLE") && Token::tokens.at(i+1).type == ("EQUALS") && Token::tokens.at(i+2).type!=("EQUALS"));
}

bool isMutatedvariable(){

}

Scope::Scope(string name, string type){
    this->name = name;
    this->type = type;
}
void Scope::addVariable(string name, int value){
    this->variables.insert(pair<string, int>(name, value));
}
void Scope::addParameter(string parameter){
    this->parameters.push_back(parameter);
}

int main(){
    /* FIRST STEP */
    //get flex input
    vector<string> flexInput = getFlexInput();

    //STEP 2:
    //Create Token objects
    Token::createTokenObjs(flexInput);

    //STEP 3:
    // create scopes
    for(int i = 0; i < Token::tokens.size()-2; i++){
        int j = i + 1;

        // CASE: function, we have a head of scope which is the function definition
        if(Token::tokens.at(i).type == "FUNCTION"){
            // create a head of Scope
            struct Node * head;

            // finding indexes
            int defIndex = Token::tokens.at(i).content.find("def");
            int functionNameIndexStart = defIndex+4;
            int openParanthesisIndex = Token::tokens.at(i).content.find("(");
            int closeParanthesisIndex = Token::tokens.at(i).content.find(")");
            int functionNameIndexEnd = openParanthesisIndex-1;

            // defining scope
            Scope *functionDef = new Scope(Token::tokens.at(i).content.substr(functionNameIndexStart, functionNameIndexEnd - functionNameIndexStart+1), "FUNCTION");

            // defining function parameters
            string parameters = Token::tokens.at(i).content.substr(openParanthesisIndex,closeParanthesisIndex-openParanthesisIndex+1);
            vector<string> functionParameters = split(parameters, ",");
            // assigned the function its associated parameters
            for(int i = 0; i < functionParameters.size(); i++){
                functionDef->parameters.push_back(functionParameters.at(i));
            }

            head->data = functionDef;
            head->prev = NULL;
            head->next = NULL;
            while(Token::tokens.at(j).level>= Token::tokens.at(i).level){
                if(Token::tokens.at(j).type == "KEYWORD"){
                    Scope *scope = new Scope("", Token::tokens.at(j).type);
                    appendToDLL(&head, scope);
                }
                j++;
            }
            functionScopes.push_back(head);
        }
        // CASE: IF OUTSIDE OF FUNCTION
        // CASE: ELSE OUTSIDE OF FUNCTION
    }


//    for(int i = 0; i < Token::tokens.size()-2; i++){
//        if (isVariableAssignment(i)){
//            Token::variables.insert(pair<Token, Token> (Token::tokens.at(i),Token::tokens.at(i+2)));
//        }
//    }

    // recognize function calls and addVariable() to the appropriate scope


    return 0;
}