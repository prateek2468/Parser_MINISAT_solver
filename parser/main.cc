#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "parser.h"
#include "treeNode.h"

// a helper function parsing the input into the formula string and the assignment string
void parseLine(const std::string &line, std::string &formulaStr, std::string &assignmentStr) {
  // your code starts here
  std::string delimiter =";" ;
  int find = line.find(delimiter) ;  
  if(find == line.npos){
    throw 1 ; 
  }
  formulaStr = line.substr(0 , find) ; 
  assignmentStr = line.substr(find+1) ; 
  if(formulaStr.length() == 0 && assignmentStr.length() == 0){
    throw 1 ; 
  }

  // removing whitespaces in both assignment and formula 
  formulaStr.erase(remove(formulaStr.begin(), formulaStr.end(), ' '), formulaStr.end() ); 
  assignmentStr.erase(remove(assignmentStr.begin(), assignmentStr.end(), ' '), assignmentStr.end() ); 

  AssignmentParser a(assignmentStr) ; 
  std::map<std::string, bool> map = a.parseAssignment() ; 
  

  FormulaParser p(formulaStr ) ; 
  TreeNode * root = p.getTreeRoot() ; 

  bool ans = root->evaluate(map) ;
  std::cout << ans  << std::endl; 
   
  

}



// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
  try{
  while (true) // continuously asking for new inputs from standard input
  {
    std::string line; // store each input line
    std::string formulaStr; // store the formula string
    std::string assignmentStr; // store the assignment string
    // your code starts here
    //getline ( std::cin , line) ;
    
    while (std::getline(std::cin, line)){
    parseLine(line , formulaStr, assignmentStr);
    }
    
    
  }
  }catch(int a){
    if(a == 1){
      std::cout<<"Error: invalid input" <<std::endl; 
      main() ; 
    }else if(a == 2){
      std::cout<< "Error: contradicting assignment" << std::endl; 
      main() ; 
    }else if(a ==3 ){
      std::cout<< "Error: incomplete assignment" << std::endl ; 
      main() ; 
    }
    

  }
}

