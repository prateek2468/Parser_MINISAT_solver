#include "tokenizer.h"

Tokenizer::Tokenizer() {}


Tokenizer::Tokenizer(std::string ln , std::string check) {
  // complete the constructor
  
  index= 0 ;
  bracket=0 ; 
  //counting the number of assignments 
  if(check.compare("a") == 0){
      if(ln.length() == 0){
        length =1 ; 
      }else{
        int temp = std::count(ln.begin(), ln.end(), ',');
        length = temp+1 ; 
      }

      arr.resize(length) ; 
  int prv =0 ; 
  std::string sub = std::string(ln) ; 
  for(int i=0 ; i<ln.length() ; i++){
    if(ln.at(i) == ','){
      Token *t = new Token ; 
      std::string temp = sub.substr(prv , (i-prv)) ; 
      t->content = temp ;  
      prv = i+1 ;
      arr.insert(arr.begin() , *t) ; 
    }
    if(i == ln.length()-1){
      std::string temp = ln.substr(prv ) ;
      Token t ; 
      t.content = temp ;  
      arr.insert(arr.begin() , t) ;
    }
  }
  //std::cout<<index<<".   "<<length << "\n" ;  
  }else{ 
    arr.resize(ln.length()) ; 
    std::string temp = "" ; 

    for(int i=0 ; i<ln.length() ; i++){
        int a = ln.at(i) ; 
        if((a>=40 && a<=43) || (a== 45) || (a>=48 && a<=57) || (a>=65 && a<=90) || (a>=97 && a<=122) ){
        }else{ 
          throw 1 ; 
        }
        if(ln.at(i) == '+' || ln. at(i) == '*' || ln.at(i) == '-' || ln.at(i) == '(' || ln.at(i) == ')'){
            if(temp.length() != 0){
              Token t ; 
              t.content = temp ; 
              t.type = "variable" ; 
              arr.insert(arr.begin() , t) ; 
              temp = "" ; 
              length++ ; 
            }
            if(ln.at(i) == '('){
              bracket++ ; 
            }else if(ln.at(i) == ')'){
              bracket -- ; 
            }
            Token t ; 
            t.content = ln.at(i) ; 
            t.type = "operator";
            arr.insert(arr.begin() , t) ; 
            length++ ; 
        }else if((ln.at(i) == '0' || ln.at(i) == '1')){
          if(temp.length() == 0){
          Token t ; 
          t.content = ln.at(i) ; 
          t.type = "constant";
          arr.insert(arr.begin() , t) ; 
          length++ ; 
          }else{
            temp = temp + ln.at(i) ;
          }
        }
        else{
          temp = temp+ln.at(i) ; 
        }
    }
    if(temp.length() != 0){
              Token t ; 
              t.content = temp ; 
              t.type = "variable" ; 
              arr.insert(arr.begin() , t) ;  
              length++ ; 
            }
    
  } 
  arr.resize(length) ;
  std::reverse(arr.begin() , arr.end()) ; 
  if(bracket!=0){ 
    throw 1; 
  }

}

bool Tokenizer::advanceToken() {
  // your code starts here
  bool const t = true ; 
  if((index+1) <length ){
      index++ ; 
      return t ; 
  }
  return false;
}

Token Tokenizer::getAdvanceToken() {
  Token resultToken;
  // your code starts there
  resultToken = arr.at(index+1) ;
  return resultToken;
}

bool Tokenizer::hasToken() const {
  // your code starts here
  bool const t = true ; 
  if(index <length){
    return t ; 
  }else{
  return false;}
}

bool Tokenizer::getBack(){
  index-- ; 
  return true ; 
}

// only can be called when hasToken() is true
Token Tokenizer::getToken() {
  Token resultToken;
  // your code starts there
  
  resultToken = arr.at(index) ; 
  return resultToken;
}
