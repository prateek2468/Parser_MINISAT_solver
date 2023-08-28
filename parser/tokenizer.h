#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <regex>
#include <algorithm>
#include <sstream>
#include <vector>
#include<iostream>
#include <string>

struct Token
{
    std::string content;
    std::string type;
};

// a tokenzier breaks a stream of string into tokens
class Tokenizer
{
  // your code starts here
  std::vector<Token> arr ; 
  public: 
    Tokenizer() ; 
    int index ; 
    int length ; 
    int bracket ; 
    Tokenizer(std::string ln , std::string check);
    bool advanceToken(); // advance to the next token; return false if no more token exist
    bool hasToken() const; // check whether there is a current token
    Token getToken(); // returns the token being processed
    Token getAdvanceToken() ; 
    bool getBack()  ;

};

#endif
