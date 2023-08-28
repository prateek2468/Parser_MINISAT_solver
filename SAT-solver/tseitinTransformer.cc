#include "tseitinTransformer.h"

TseitinTransformer::TseitinTransformer(TreeNode *root): formulaRoot(root) {
  
}

int TseitinTransformer::transSubformula(TreeNode* subRoot) {
  // your code starts here
  if(subRoot->getLeftChild() == NULL && subRoot->getRightChild() ==NULL){
    // variable 
    std::map<std::string, int>::const_iterator pos = varIdTable.find(subRoot->getContent()) ; 

    if( pos == varIdTable.end() ){
    varIdTable[subRoot->getContent()] = varIdCounter ; 
    int value = varIdCounter ; 
    varIdCounter++ ; 
    return value ; 
    }else{
      return pos->second ; 
    }
  }
  int value1 , value2 ; 
  int value  = varIdCounter ; 
  varIdCounter++; 
  if(subRoot->getLeftChild() != NULL ){
     value1 = transSubformula(subRoot->getLeftChild()) ; 
  }

  if(subRoot->getRightChild() != NULL){
     value2 = transSubformula(subRoot->getRightChild()) ; 
  }

  if(subRoot->getContent() == "-"){
    addNegEq(value , value1);
    // int value  = varIdCounter ; 
    // varIdCounter++; 
    return value ; 
  }else if(subRoot->getContent() == "*"){
    addAndEq(value , value1 , value2) ; 
    // int value = varIdCounter ; 
    // varIdCounter++ ; 
    return value ; 

  }else if(subRoot->getContent() == "+"){
    addOrEq(value , value1 , value2) ; 
    // int value = varIdCounter ; 
    // varIdCounter++ ; 
    return value ; 

  }
  return 0;
}

void TseitinTransformer::addNegEq(int curID, int childID) {
  // your code starts here
  std::vector<int> temp ; 
  temp.insert(temp.begin() , curID ) ; // p <-> -q  === (p V q ) A (-p V -q ) \\\\\ (p V q) 
  temp.insert(temp.begin() , childID) ; // (p V q)

  std::vector<int> temp1 ; 
  int tempCur = curID* -1 ; //(-p V -q)
  int tempChildId = childID* -1 ; // (-p V -q)
  temp1.insert(temp1.begin() , tempCur) ; 
  temp1.insert(temp1.begin() , tempChildId) ;

  cnf.insert(cnf.begin() , temp) ; 
  cnf.insert(cnf.begin() , temp1) ; 
}

void TseitinTransformer::addOrEq(int curID, int leftID, int rightID) {
  // your code starts here
  

  int tempCur = curID*-1 ; 
  int tempLeft = leftID*-1 ; 
  int tempRight = rightID*-1 ; 

  std::vector<int> temp ;
  temp.insert(temp.begin() , curID) ; // (c V -l) 
  temp.insert(temp.begin() , tempLeft) ; 

  std::vector<int> temp1 ; 
  temp1.insert(temp1.begin() , curID) ;// (c V -r)
  temp1.insert(temp1.begin() , tempRight) ;    

  std::vector<int> temp2 ; 
  temp2.insert(temp2.begin() , leftID) ; // (r V l V -c)
  temp2.insert(temp2.begin() , rightID) ;
  temp2.insert(temp2.begin() , tempCur) ;  

  cnf.insert(cnf.begin() , temp) ; 
  cnf.insert(cnf.begin() , temp1) ; 
  cnf.insert(cnf.begin() , temp2) ;  

}

void TseitinTransformer::addAndEq(int curID, int leftID, int rightID) {
  // your code starts here
  int tempCur = curID*-1 ; 
  int tempLeft = leftID*-1 ; 
  int tempRight = rightID*-1 ; 

  std::vector<int> temp ;
  temp.insert(temp.begin() , tempCur) ; // (-c V l) 
  temp.insert(temp.begin() , leftID) ; 

  std::vector<int> temp1 ; 
  temp1.insert(temp1.begin() , tempCur) ;// (-c V r)
  temp1.insert(temp1.begin() , rightID) ;    

  std::vector<int> temp2 ; 
  temp2.insert(temp2.begin() , tempLeft) ; // (-r V -l V c)
  temp2.insert(temp2.begin() , tempRight) ;
  temp2.insert(temp2.begin() , curID) ;  

  cnf.insert(cnf.begin() , temp) ; 
  cnf.insert(cnf.begin() , temp1) ; 
  cnf.insert(cnf.begin() , temp2) ;


}

std::vector<std::vector<int> > TseitinTransformer::transform() {
  // your code starts here
  transSubformula(formulaRoot) ; 
  
  std::vector<int> temp ;
  temp.insert(temp.begin() , 1) ;

  cnf.insert(cnf.begin() , temp) ;  

  return cnf;
}

std::string TseitinTransformer::cnfString() const {
  std::string result = "";
  // your code starts here
  return result;
}

unsigned int TseitinTransformer::getVarNum() const {
  // your code starts here
  return 0;
}
