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
map<string, int>functions; //map function name to starting line where it is defined
// pointers to function scope blocks
vector<Node*>functionScopes;
Scope*  Main::globalScope = new Scope("","global");
map<string, string>Main::globalVariables;

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
        return Main::do_arithmetic(thingsToAssign);
    } else
        return thingsToAssign[0];
}

//helper function for performAssignment()
string Main::do_arithmetic(vector<string> arstr){

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

bool isfunctioncallAssignment(int i){
    return (Token::tokens.at(i).type == "VARIABLE" && Token::tokens.at(i+1).type == "EQUALS" && Token::tokens.at(i+2).type=="FUNCTIONCALL");
}

bool isVariableAssignment(int i){
    return (Token::tokens.at(i).type == "VARIABLE" && Token::tokens.at(i+1).type == "EQUALS" && (Token::tokens.at(i+2).type=="INTEGER" || Token::tokens.at(i+2).type=="VARIABLE"));
}

bool isMutatedvariable(){
}

int scope_engine(int i, Scope *scope)
{
    //while inside the scope
    while(Token::tokens.at(i).level+1 >= scope->level){ //>= experimental
        int current_line = Token::tokens.at(i).line;


        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        //CASE:
        // Variable Assignment
        if(isVariableAssignment(i)){
            string value = performAssignment(i + 2, scope, current_line);
            if(Token::tokens.at(i).level == 0){ // GLOBAL VARIABLE
                Main::globalScope->addVariable(Token::tokens.at(i).content, value);
            }else { //LOLCAL SCOPE
                scope->addVariable(Token::tokens.at(i).content, value);
            }
            while(Token::tokens.at(i).line==current_line){
                i++;
            }
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
                Scope * scope1 = new Scope("","if");
                scope1->level = Token::tokens.at(i).level;
                scope1->line = Token::tokens.at(i).line;
                //move to next line //move to inside of if
                int if_line = Token::tokens.at(i).line;
                while(if_line == Token::tokens.at(i).line)
                    i++;
                return scope_engine(i, scope1);
                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                //CASE:
                //ELSE
            }else
                {
                //move to next line //move to out of if scope
                int if_line = Token::tokens.at(i).line;
                int if_level = Token::tokens.at(i).level;
                i = i + 1;
                while(if_line == Token::tokens.at(i).line)
                    i++;
                while(if_level < Token::tokens.at(i).level)
                    i++;
                // go to else if there is one!
                for(int t = i; t < Token::tokens.size(); t++){
                    if((Token::tokens.at(t).content.find("else:") != string::npos) && Token::tokens.at(t).level == if_level){
                        i = t;
                        Scope * scope1 = new Scope("","else");
                        scope1->level = Token::tokens.at(i).level;
                        scope1->line = Token::tokens.at(i).line;
                        return scope_engine(i, scope1);
                    }
                }
            }

        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        //CASE
        //PRINT
        if(Token::tokens.at(i).type == "FUNCTIONCALL" && Token::tokens.at(i).content.find("print")!=string::npos){
            Main::print(i, scope);
            //move to next line
            while(current_line == Token::tokens.at(i).line)
                i++;
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        //CASE
        //RETURN
        if(Token::tokens.at(i).type == "RETURN"){
            int current_line = Token::tokens.at(i).line;
            while(Token::tokens.at(i).line==current_line){
                i =i+1;
                if(scope->variables.find(Token::tokens.at(i).content)!=scope->variables.end()){
                    return stoi(scope->variables.at(Token::tokens.at(i).content));
                }else
                    return stoi(Token::tokens.at(i).content);
                i++;
            }
        }
    }
    return -111; //done --> no function
}

void Main::print(int i, Scope* scope) {
    string content = Token::tokens.at(i).content;
    int open_par = content.find("(");
    int close_par = content.find(")");
    string thing_to_print = content.substr(open_par+1, close_par-open_par-1);
    int string_start;
    int string_end;
    int curr = 0;
    do{
        //covering for the case that the comma is part of a string
       if(thing_to_print.find("\"", curr)!=string::npos){
           string_start = thing_to_print.find("\"", curr);
           string_end = thing_to_print.find("\"", string_start+1);
           cout << thing_to_print.substr(1, thing_to_print.find(",", string_end)-2); //print with removed double quotes
           curr = string_end + 1;
       }else{ // print int or look up var value and print int
           string var = thing_to_print.substr(curr+1, thing_to_print.find(",", curr));
           if(var.find_first_not_of( "0123456789" ) == string::npos){ //IF INT
               cout << thing_to_print.substr(curr+1, thing_to_print.find(",", curr));
           }else{
               //IF VAR
               if(scope->variables.find(var)!=scope->variables.end()){ //LOCAL SCOPE
                   cout <<  (scope->variables.at(Token::tokens.at(i).content));
               }
               else if(globalScope->variables.find(var)!=globalScope->variables.end()){ //GLOBAL SCOPE
                   cout << (globalScope->variables.at(var));
               }
//               else if(functions.find(Token::tokens.at(i).content)!=functions.end()) {
//                    cout << functions.at(Token::tokens.at(i).content);
//               }

           }
           curr = thing_to_print.find(",", curr) + 1;
       }


    }while( curr < thing_to_print.size() && thing_to_print.find(",", curr) != string::npos);
    cout << endl;
}

int main(){

    //instantiate global variables
    Main::globalScope->variables = Main::globalVariables;


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
        if(Token::tokens.at(i).type == "FUNCTION")
        {
            // create a head of Scope

            // finding indexes
            int defIndex = Token::tokens.at(i).content.find("def");
            int functionNameIndexStart = defIndex+4;
            int openParanthesisIndex = Token::tokens.at(i).content.find("(");
            int closeParanthesisIndex = Token::tokens.at(i).content.find(")");
            int functionNameIndexEnd = openParanthesisIndex-1;

            // defining scope
            Scope *functionDef = new Scope(Token::tokens.at(i).content.substr(functionNameIndexStart, functionNameIndexEnd - functionNameIndexStart+1), "FUNCTION"); // +1 to make up for index 0
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
            functionDef->lexer_line = i;

            i = i + 1; //move forward

            // store function name and skip function def until FUNCTIONCALL
            //FUNCTION: line number, number of parameters, name

            while(functionDef->level  <  Token::tokens.at(i).level){
                i++; //skip entire function
            }

            struct Node *head = new Node(functionDef);
            functionScopes.push_back(head);
        }
        // TODO: cover for functioncall assignment to variable
        if(Token::tokens.at(i).type == "FUNCTIONCALL" && Token::tokens.at(i).content.find("print") == string::npos)
        {
            vector<Node *>::iterator it = find_if(functionScopes.begin(), functionScopes.end(), [i](Node *n) {
                return n->data->name == getFunctionNameFromFunctionCall(Token::tokens.at(i).content);
            });
            // if the function exists
            if(*it !=  NULL){
                vector<string> params = getFunctionCallValuesToVariables(Token::tokens.at(i).content);
                // plug in/assign function call values to function paramaters
                for(int i = 0; i < params.size() && params[0]!=""; i++){
                    std::map<string, string>::iterator m_it = it.operator*()->data->variables.find(it.operator*()->data->parameters.at(i));
                    m_it->second = params.at(i);
                }
                //call function
                int return_value = scope_engine(it.operator*()->data->lexer_line+1, it.operator*()->data);
                // store return_value for that function name
                functions.insert((pair<string, int> (it.operator*()->data->name,return_value)));
            }
            else{
                cout << "TypeError: 'int' object is not iterable" << endl;
                cout << "[INFO] You tried to call a function that hasn't yet been declared/defined." << endl;
            }
        }else {
            Scope * scope = new Scope("",Token::tokens.at(i).type);
            scope->level = Token::tokens.at(i).level;
            scope->line = Token::tokens.at(i).line;
            scope->lexer_line = i;
            scope_engine(i, scope);
        }
    }
    return 0;
}

