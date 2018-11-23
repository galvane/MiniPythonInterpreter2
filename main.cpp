#include<iostream>
#include<fstream>
#include <vector>
#include <map>
#include <cmath>
#include <cstdio>
#include <set>
#include <algorithm>

#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "main.h"
#include "token.h"
#include "node.h"

using namespace std;

vector<Token>Token::tokens;
map<Token, Token>Token::globalVariables;

string getFunctionNameFromFunctionCall(string functionCall){
    int open_par = functionCall.find("(");
    const string functionName = functionCall.substr(0, open_par);
    if (functionName.find(" ") != string::npos)
        return functionName.substr(0, functionName.find(" "));
    else
        return functionName;
}

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
    parameters.push_back(str);
    return parameters;
}


// pointers to function scope blocks
vector<Node*>functionScopes;

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
            vector<string> functionParameters = split(parameters.substr(1,parameters.size()-2), ",");
            // assigned the function its associated parameters
            for(int i = 0; i < functionParameters.size(); i++){
                functionDef->parameters.push_back(functionParameters.at(i));
                //functionDef->variables[functionParameters.at(i)] = "";
                functionDef->variables.insert(pair<string,string>(functionParameters.at(i), ""));
            }

            struct Node *head = new Node(functionDef);

            // while we are still inside the function:
            while(Token::tokens.at(j).level > Token::tokens.at(i).level){

                if(Token::tokens.at(j).type == "KEYWORD"){
                    Scope *scope = new Scope("", Token::tokens.at(j).content);
                    Node::appendToDLL(&head, scope);
                }

                //variable assignments
                if(Token::tokens.at(j).type == "VARIABLE" && Token::tokens.at(j+1).type == "EQUALS"){
                    functionDef->variables.insert(pair<string,string>(Token::tokens.at(j).content, Token::tokens.at(j+2).content));
                }
                j++;
            }
            functionScopes.push_back(head);

        }
        if(Token::tokens.at(i).type == "FUNCTIONCALL"){
            //&& find(functionScopes.begin(), functionScopes.end(),getFunctionNameFromFunctionCall(Token::tokens.at(i).content))!=functionScopes.end()){

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