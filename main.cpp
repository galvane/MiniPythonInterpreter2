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

//int line;
//string type;
//string content;
//int level; //level of indent
vector<Token>Token::tokens;
map<Token, Token>Token::variables;

/* SCOPE */
//string name;
//string type;
//map<string,int> variables;
//vector<string> parameters;

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
    return (Token::tokens.at(i).type == ("VARIABLE") && Token::tokens.at(i+1).type == ("EQUALS") && Token::tokens.at(i+2).type!=("EQUALS");
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
    //create variable storage for
    // functions
    // if blocks
    // else blocks
    for(int i = 0; i < Token::tokens.size()-2; i++){
        if (isVariableAssignment(i)){
            Token::variables.insert(pair<Token, Token> (Token::tokens.at(i),Token::tokens.at(i+2)));
        }
    }

    // recognize function calls and addVariable() to the appropriate scope


    return 0;
}