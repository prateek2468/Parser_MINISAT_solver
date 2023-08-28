#include "treeNode.h"

TreeNode::TreeNode(std::string cntt): content (cntt) {
  leftChild = nullptr ; 
  rightChild = nullptr ; 
}

std::string TreeNode::getContent() const {
  // your code starts here
  return content;
}

TreeNode *TreeNode::getLeftChild() const {
  // your code starts here
  if(leftChild!= NULL){
    return this->leftChild ; 
  }
  return nullptr;
}
TreeNode *TreeNode::getRightChild() const {
  // your code starts here
  if(rightChild!= NULL){
    return this->rightChild ; 
  }
  return nullptr;
}

void TreeNode::updateLeftChild(TreeNode *lChild) {
  // your code starts here
  this->leftChild = lChild ; 
}

void TreeNode::updateRightChild(TreeNode *rChild){
  this->rightChild = rChild ; 
}

void TreeNode::updateChildren(TreeNode *lChild, TreeNode *rChild) {
  // your code starts here
  this->leftChild = lChild ; 
  this->rightChild = rChild ; 

}

OperatorNode::OperatorNode(std::string cntt): TreeNode(cntt) {
  TreeNode* left ; 
  TreeNode* right ; 
}

bool OperatorNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  std::string temp = this->getContent() ; 
  bool a ; 
  bool b  ; 
  TreeNode *a1  = this->getLeftChild() ; 
  TreeNode *b1  = this->getRightChild() ; 
  if(temp.compare("+") == 0){
    a = false ; 
    b = false ; 
    if(a1 != nullptr ){
      a = a1->evaluate(assignment) ; 
    }
    if(b1 != nullptr){
      b = b1->evaluate(assignment) ; 
    }
    //std::cout<<temp << "\t" << a <<"\t"<< b << "\t" <<(a||b) << "\n" ;
    return a||b ; 
  }else if(temp.compare("-") == 0){
    a = a1->evaluate(assignment) ;
    //std::cout<<"-" <<"\t" <<a <<"\n" ; 
    return !a ;  
     
  }else if(temp.compare("*") == 0){
    
    a = true ; 
    b = true ; 
    if(a1 != nullptr ){
      a = a1->evaluate(assignment) ; 
    }
    if(b1 != nullptr){
      b = b1->evaluate(assignment) ; 
    }
    //std::cout<<temp <<"\t" << (a&&b) << "\n";
    return a&&b ; 
  }else{
    throw 1 ; 
  }

  return false;
}

ConstantNode::ConstantNode(std::string cntt): TreeNode(cntt) {}


bool ConstantNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  if(this->getContent().compare("1") == 0){
    return true ; 
  }else if(this->getContent().compare("0") == 0){
    return false ; 
  }else{
     throw 1 ;  
  }
  return false;
}

VariableNode::VariableNode(std::string cntt): TreeNode(cntt) {}

bool VariableNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here

  std::map<std::string,bool>::iterator it;
  std::string temp = this->getContent() ; 
  

    if(assignment.find(temp) != assignment.end()){  
       return assignment.at(temp) ; 
    }else{
      //throw error 
      throw 3 ;  
    }
  
}

TreeNode::~TreeNode() {
  // your code starts here
}
