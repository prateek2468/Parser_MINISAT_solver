#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"

FormulaParser::FormulaParser(std::string ln ){
  this->tknzr= new Tokenizer(ln , "f"); 

}

TreeNode *FormulaParser::parseConjTerm() {
  // your code starts here
  if(tknzr->hasToken()){
    //std::cout<<tknzr->index << "\t" << "inside parseConjterm" << "\n"; 
    TreeNode *t= parseTerm() ; 
    if(tknzr->advanceToken()){
      Token temp = tknzr->getToken()  ; 
      if(temp.content.compare("*") == 0 ){ 
        //std::cout<<"* deteched" << "\n" ; 
        OperatorNode * o = new OperatorNode("*") ; 
        tknzr->advanceToken() ; 
        o->updateChildren(t , parseConjTerm()) ; 
        return o ; 
      }else{
        tknzr->getBack() ; 
      }
    }

    return t ; 
  }
  return nullptr;
}

TreeNode *FormulaParser::parseTerm() {
  // your code starts here
  if(tknzr->hasToken()){
    //std::cout<<tknzr->index << "\t" << "inside parseTerm" << "\n"; 
    Token temp = tknzr->getToken() ; 
    //std::cout<<temp.content << "\n" ; 
    if(temp.content.length()>0){
    if(temp.content.at(0) == '('){
        tknzr->advanceToken() ; 
        TreeNode *t4 = parseFormula() ;
        return t4 ; 
    }else if(temp.content.compare(")") == 0){
        if(tknzr->advanceToken() ){
        TreeNode *t1 = parseConjTerm() ;   
        return t1 ; 
        }else{
          return nullptr ; 
        }
      }else if(temp.type.compare("variable")==  0 ){
      VariableNode* v = new VariableNode(temp.content);
      return v ; 
    }else if(temp.type.compare("constant") == 0){
      ConstantNode* t2 = new ConstantNode(temp.content) ;
      return t2 ; 
    }else if(temp.content.at(0) == '-'){
        OperatorNode* o = new OperatorNode("-") ;
        if(tknzr->advanceToken()){
          Token temp1 = tknzr->getToken() ; 
          if(temp1.content.compare("operator") != 0){
            TreeNode* t = parseTerm() ; 
            
            o->updateLeftChild(t);
            return o ; 
          }else{
            //throw error
            throw 1 ; 
          }
        }else{
          //throw error
          throw 1 ;
        }
    }
    }
    // else{
    //   std::cout<<"this error 2"<<"\n"; 
    //   std::cout<<temp.content << "\t" << temp.type << "\n" ; 
    //   throw 1 ; 
    // }
  }
  return nullptr;
}

TreeNode *FormulaParser::parseFormula() {
  // your code starts here
  while(tknzr->hasToken()){
    //std::cout<<tknzr->index << "\t" << "inside parseFormula" << "\n"; 
    TreeNode* t = parseConjTerm() ;
    if(tknzr->advanceToken()){
      Token temp = tknzr->getToken()  ; 
      if(temp.content.compare("+") == 0 ){  
        OperatorNode * o = new OperatorNode("+") ; 
        tknzr->advanceToken() ; 
        TreeNode * right = parseFormula() ; 
        //std::cout<<"Error here :- "<<right->getContent()<<"\n""\n" ;  
        o->updateChildren(t , right) ; 
        return o ; 
       }else{
        if(tknzr->hasToken()){
          TreeNode *t1 = parseFormula() ; 
          if(t1!=nullptr){
            t1->updateLeftChild(t) ; 
          } 
        }
      }
      }
    return t ; 
  }
  return nullptr;
}

TreeNode * FormulaParser::getTreeRoot() {
  // your code starts here
  TreeNode *root = parseFormula();
  //T(root , 0) ; 
  return root;
}

void FormulaParser::T(TreeNode * root , int i){
  std::cout << "Level "<<i << ":-  "<<"root :- " << root->getContent() << "\t"; 
  if(root->getLeftChild() !=  nullptr){
     std::cout<<"left:- "<< root->getLeftChild()->getContent() <<"\t"; 
     
     }
  if(root -> getRightChild() != nullptr ){
    std::cout<<"right:- "<< root->getRightChild()->getContent() ;
     }
    std::cout<<"\n" ; 

  if(root->getLeftChild() !=  nullptr){
     T(root->getLeftChild() , i+1) ; 
     
     }
  if(root -> getRightChild() != nullptr ){
    T(root->getRightChild() , i+1) ; }
}

FormulaParser::~FormulaParser() {
  // your code starts here
}

AssignmentParser::AssignmentParser(){}

AssignmentParser::AssignmentParser(std::string ln){
  this->tknzr= new Tokenizer(ln , "a"); 
}


std::map<std::string, bool> AssignmentParser::parseAssignment() {
  std::map<std::string, bool> results; 
  // your code starts here 
  bool b = true ; 
  bool b1 = false ; 
  bool flag = true ; 
  bool check  = false ; 
  std::map<std::string,bool>::iterator it;
  //going to loop for all token , getting every token's content and checking the variable name and putting it in the map
  while(this->tknzr->hasToken() && flag){
    
    std::string temp = this->tknzr->getToken().content ;
    int find = temp.find(":");
    if(find == temp.npos&& temp.length() >0 ){
      throw 1 ; 
    }
    std::string temp1 = temp.substr(0 , find) ; 
    std::string temp2 = temp.substr(find+1) ; 
     
    //checking the variable

    //checking the constant

    // putting in the map and checking if the map already has the value . 

    if(temp2.compare("1") == 0){
      check = b ; 
    }else{
       check = b1 ; 
    }
    it = results.find(temp1) ; 
    if(it != results.end()){
      
      if(check!=results[temp1]){
        //return error ;
        throw 2 ; 
      }
    }
    
    
    results[temp1] = check ; 
    flag = this->tknzr->advanceToken() ; 
  }
  return results;
}

AssignmentParser::~AssignmentParser() {
  // your code starts here

}
