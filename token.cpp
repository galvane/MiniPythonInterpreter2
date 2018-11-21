//
// Created by osboxes on 11/21/18.
//

#include "token.h"

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