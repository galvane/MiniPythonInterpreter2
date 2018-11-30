#include<iostream>
#include<fstream>
#include <vector>
#include <map>
#include <cmath>
#include <cstdio>
#include <set>
#include <algorithm>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "main.h"
#include "token.h"
#include "node.h"

using namespace std;

vector<Token>Token::tokens;
map<Token, Token>Token::globalVariables;

bool check_if(int i, Scope *scope)
{
    string if_keyword = Token::tokens.at(i).content;  i++;

    // this program only compares integers
    int num1_index;
    int num2_index;
    int comp_index;

    if(Token::tokens.at(i).content == "OPEN_PARENTHESIS") {
        //op_index is  i;
        num1_index = i+1;
        comp_index = i+2;
        num2_index = i+3;
        //cp_index is i+4
    } else{
        num1_index = i;
        comp_index = i+1;
        num2_index = i+2;
    }
    // integers we are comparing
    int num1; int num2;
    //get num1 and num2
    if(Token::tokens.at(num1_index).type == "INTEGER")
        num1 = stoi(Token::tokens.at(num1_index).content);
    else{
        //VARIABLE
        if(scope->variables.find(Token::tokens.at(num1_index).content)!=scope->variables.end()){
            num1 = stoi(scope->variables.at(Token::tokens.at(num1_index).content));
        }
    }

    if(Token::tokens.at(num2_index).type == "INTEGER")
        num2 = stoi(Token::tokens.at(num2_index).content);
    else{
        //VARIABLE
        if(scope->variables.find(Token::tokens.at(num2_index).content)!=scope->variables.end()){
            num2 = stoi(scope->variables.at(Token::tokens.at(num2_index).content));
        }
    }

    if(Token::tokens.at(comp_index).type == "EQUALSCOMPARISON"){
        return  (num1 == num2);
    }
    else if (Token::tokens.at(comp_index).type == "GREATER_THAN"){
        return (num1 > num2);

    }
    else if(Token::tokens.at(comp_index).type == "LESS__THAN"){
        return (num1 < num2);
    }
    else{
        //!= case
        return (num1 != num2);
    }
}

void set_else_i(int i){
    else_index = i;
}

int get_else_i(){
    return else_index;
}

bool isConditionalStatement(string var1, string comparison, string var2, string colon){
    return ( (var1 == "VARIABLE" || var1 == "INTEGER")  && (var2 == "VARIABLE" || var2 == "INTEGER") && (comparison == "EQUALSCOMPARISON" || comparison == "GREATER_THAN" || comparison == "LESS_THAN") && colon == "COLON");
}

bool elseStatement(string elseContent){
    return (elseContent == "else:");
}

bool isReturnStatement(string returnKeyword){
    return (returnKeyword == "RETURN");
}

string performAssignment(int i, Scope *scope, int assignmentLine){
    bool arithmetic = false;
    vector<string> thingsToAssign;

    while(Token::tokens.at(i).line == assignmentLine){
        string line = Token::tokens.at(i).content;


        if(line.find("*")!= string::npos || line.find("+")!= string::npos || line.find("/")!= string::npos || line.find("-")!=string::npos){
            arithmetic = true;
        }
        // if rhs assignment exists --> store it as its value (integer)
        if(scope->variables.find(line)!=scope->variables.end()){
            thingsToAssign.push_back(scope->variables.at(line));
        } else
            thingsToAssign.push_back(line);
        i++;
    }
    if(arithmetic){
        return do_arithmetic(thingsToAssign);
    } else
        return thingsToAssign[0];
}

//helper function for performAssignment()
string do_arithmetic(vector<string> arstr){

    int result = 0;
    for(int i = 0; i < arstr.size()-1;i++){

        if(arstr.at(i) == "*"){
           result = result * stoi(arstr.at(i+1));
           i++;
        }
        else if(arstr.at(i) == "+" ){
            result = result + stoi(arstr.at(i+1));
            i++;
        }
        else if(arstr.at(i) == "/"){
            result = result / stoi(arstr.at(i+1));
            i++;
        }
        else if(arstr.at(i) == "-"){
            result = result - stoi(arstr.at(i+1));
            i++;
        }
        else{
            result = result + stoi(arstr.at(i));
        }
    }
    return to_string(result);

}

vector<string> getFunctionCallValuesToVariables(string functionCall){
    vector<string> paramList_;
    int open_par = functionCall.find("(");
    int close_par = functionCall.find(")");
    const string paramList = functionCall.substr(open_par+1,close_par-open_par-1);
    string pL = paramList;
    while(pL.find(",") != string::npos){
        paramList_.push_back(pL.substr(0, pL.size()-pL.find(",")));
        pL = paramList.substr(paramList.find(",")+1, string::npos);
    }
    paramList_.push_back(pL);
    return paramList_;
}

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
    return (Token::tokens.at(i).type == "VARIABLE" && Token::tokens.at(i+1).type == "EQUALS" && (Token::tokens.at(i+2).type=="INTEGER" || Token::tokens.at(i+2).type=="VARIABLE"));
}

bool isMutatedvariable(){
}

int scope_engine(int i, Scope* scope)
{
    if(Token::tokens.at(i).type == "RETURN"){
        int current_line = Token::tokens.at(i).line;
        while(Token::tokens.at(i).line==current_line){
            i++;
        }
        if(scope->variables.find(Token::tokens.at(i).content)!=scope->variables.end()){
            return stoi(scope->variables.at(Token::tokens.at(i).content));
        }else
            return stoi(Token::tokens.at(i).content);
    }

    //while inside the scope
    while(Token::tokens.at(i).level+1 > scope->level){
        int current_line = Token::tokens.at(i).line;


        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        //CASE:
        // Variable Assignment
        if(isVariableAssignment(i)){
            string value = performAssignment(i+2, scope, current_line);
            scope->addVariable(Token::tokens.at(i).content, value);
        }

        while(Token::tokens.at(i).line==current_line){
            i++;
        }


        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        //CASE:
        //IF
        bool if_result = false;
        int if_level = Token::tokens.at(i).level;
        if(Token::tokens.at(i).content.find("if")!=string::npos){
            //TODO: count to make sure total number of else's is not greater than total number of if's
            if_result = check_if(i, scope);
            if(if_result == true){
                //i = i + 1; // move to inside the if
                return scope_engine(i+1, new Scope("","if"));
            }else
                {
                // go to else
                for(int t = i; t < Token::tokens.size(); t++){
                    if((Token::tokens.at(t).content.find("else:") == string::npos) && Token::tokens.at(t).level == if_level){
                        //i = t;
                        return scope_engine(t+1, new Scope("", "else"));
                    }

                }
            }

        }


        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        //CASE:
        //ELSE

        if( (Token::tokens.at(i).content.find("else")!=string::npos) && (if_result == false) ){

        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        //CASE
        //RETURN

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        //CASE
        //PRINT

    }

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

        if(Token::tokens.at(i).type == "KEYWORD" && (Token::tokens.at(i).content.find("if")!=string::npos)){
            Scope *ifStatement = new Scope("","if");
            ifStatement->token = &Token::tokens.at(i);
            ifStatement->line = Token::tokens.at(i).line;
            if(isConditionalStatement(Token::tokens.at(i + 1).type, Token::tokens.at(i + 2).type,
                                      Token::tokens.at(i + 3).type, Token::tokens.at(i + 4).type)){
                ifStatement->conditionalStatement =
                        Token::tokens.at(i + 1).content + Token::tokens.at(i + 2).content +
                        Token::tokens.at(i + 3).content + Token::tokens.at(i + 4).content;
                i = i+5;
            }else{
                cout << "Not a valid conditional statement after \"if\"";
            }
        }

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
            for(int i = 0; i < functionParameters.size() && parameters!="()"; i++){
                functionDef->parameters.push_back(functionParameters.at(i));
                //functionDef->variables[functionParameters.at(i)] = "";
                functionDef->variables.insert(pair<string,string>(functionParameters.at(i), ""));
            }
            functionDef->line = Token::tokens.at(i).line;
            functionDef->level = Token::tokens.at(i).level;
            functionDef->token = &Token::tokens.at(i);

            i = i + 1; //move forward

            //perform all needed tasks inside of function
            scope_engine(i, functionDef);


            struct Node *head = new Node(functionDef);

//            // while we are still inside the function:
//            while(Token::tokens.at(j).level > Token::tokens.at(i).level){
//                int levelSeen = Token::tokens.at(j).level;
//
//                //if or else
//                if(Token::tokens.at(j).type == "KEYWORD"){
//                    //need to check if there is already an existing scope we need to add to
//                    if (Token::tokens.at(j).level < levelSeen && Token::tokens.at(j).type == "KEYWORD")
//                    {
//                        //add to appropriate scope instead
//                        //this is for evaluation
//                    }
//                    //while there is more if/else nesting
//                    while(Token::tokens.at(j).type == "KEYWORD") {
//
//                        Scope *scope = new Scope("", Token::tokens.at(j).content);
//                        scope->level = Token::tokens.at(j).level;
//
//                        if (isConditionalStatement(Token::tokens.at(j + 1).type, Token::tokens.at(j + 2).type,
//                                                   Token::tokens.at(j + 3).type, Token::tokens.at(j + 4).type)) {
//                            scope->conditionalStatement =
//                                    Token::tokens.at(j + 1).content + Token::tokens.at(j + 2).content +
//                                    Token::tokens.at(j + 3).content + Token::tokens.at(j + 4).content;
//                            //scope->token = &Token::tokens.at(j);
//                            j = j + 5;
//                        }
//                        if (elseStatement(Token::tokens.at(j).content)) {
//                        }
//
//                        // return consists of all items on that level
//                        if (isReturnStatement(Token::tokens.at(j).type)) {
//                            int returnLevel = Token::tokens.at(j).level;
//                            string returnStatement = "";
//                            while (returnLevel == Token::tokens.at(j).level) {
//                                returnStatement += Token::tokens.at(j).content;
//                                if (Token::tokens.at(j).type == "RETURN")
//                                    returnStatement += " ";
//                                j++;
//                            }
//                            scope->returnStatement = returnStatement;
//                        }
//
//                        if(Token::tokens.at(j).type == "PRINT_STATEMENT" && Token::tokens.at(j).level >= levelSeen){
//                            scope->printStatement = Token::tokens.at(j).content;
//
//                        }
//                        levelSeen = Token::tokens.at(j).level;
//                        Node::appendToDLL(&head, scope);
//                    }
//
//                }
//
//                //variable assignments
//                if(Token::tokens.at(j).type == "VARIABLE" && Token::tokens.at(j+1).type == "EQUALS"){
//                    functionDef->variables.insert(pair<string,string>(Token::tokens.at(j).content, Token::tokens.at(j+2).content));
//                }
//
//                //recursive --> another function call
//                if(Token::tokens.at(j).type == "FUNCTIONCALL"){
//
//                }
//                j++;
//            }
            functionScopes.push_back(head);

        }

        if(Token::tokens.at(i).type == "FUNCTIONCALL") {
            vector<Node *>::iterator it = find_if(functionScopes.begin(), functionScopes.end(), [i](Node *n) {
                return n->data->name == getFunctionNameFromFunctionCall(Token::tokens.at(i).content);
            });
            // if the function exists
            if(*it !=  NULL){
                vector<string> params = getFunctionCallValuesToVariables(Token::tokens.at(i).content);
                // plug in/assign function call values to function paramaters
                for(int i = 0; i < params.size(); i++){
                    std::map<string, string>::iterator m_it = it.operator*()->data->variables.find(it.operator*()->data->parameters.at(i));
                    m_it->second = params.at(i);
                }
            }
            else{
                cout << "TypeError: 'int' object is not iterable" << endl;
                cout << "[INFO] You tried to call a function that hasn't yet been declared/defined." << endl;
            }
        }
            //getFunctionNameFromFunctionCall(Token::tokens.at(i).content))!=functionScopes.end()

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