#include "tseitinTransformer.h"
#include "satSolver.h"
#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "parser.h"
#include "treeNode.h"
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"


// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF

int print_(TreeNode *root , int i ){
  if(root == NULL){
    return 0 ; 
  }
  std::cout<<"TreeNode at level :- "<< i << "\t" << "value :- " << root->getContent()<< "\t" ; 
  bool a , b ; 
  if(root->getLeftChild() != NULL){
     std::cout<< "leftvalue :- " << '\t' << root->getLeftChild()->getContent() <<"\t" ; 
     a = true ; 
  }

  if(root-> getRightChild() != NULL){
    std::cout<< "leftvalue :- " << '\t' << root->getRightChild()->getContent() ;
    b = true ;
  }
  std::cout<<"\n" ; 
  if(a == true) print_(root->getLeftChild() , i+1) ; 
  if(b == true) print_(root->getRightChild() , i+1) ; 
  return 0; 
}

int main() {
  while (true) // continuously asking for new inputs from standard input
  {
    std::string line; // store each input line
    // your code starts here

    std::getline(std::cin, line);
    if (std::cin.eof()) break;

    //left for parse line 

    FormulaParser fParser(line);
    TreeNode *treeRoot = nullptr;
    try {
      treeRoot = fParser.getTreeRoot();
      //int p = print_(treeRoot, 1) ; 
      TseitinTransformer t (treeRoot) ; 
      std::vector<std::vector<int> > cnf =   t.transform() ; 
      
      //printing hashmap 
      // std::map<std::string, int>::iterator itr;
      // for (itr = t.varIdTable.begin(); itr != t.varIdTable.end(); ++itr) {
      //   std::cout<<"hashamp includes :-" << '\t' << itr->first << '\t' << itr->second
      //        << '\n';
      // }


      //printing cnf 
      // std::cout<< "the cnf is :- "<<"\n" ;
      // for(int i=0 ; i<cnf.size() ; i++){
      //   for(int j=0 ; j<cnf[i].size() ; j++){
      //     std::cout<< cnf[i][j] << " " ; 
      //   }
      //   std::cout<<"\t" ; 
      // }

      unsigned int i = t.varIdCounter   ; 

      bool result = satCallingMiniSat(i ,  cnf);
      if(result == true){
        std::cout<<"sat"<< std::endl ; 
      }else{
        std::cout<<"unsat" <<std::endl; 
       }

    } catch (const char *e) {
      delete treeRoot;
      std::cout << e << std::endl;
      continue;
    }
    delete treeRoot;
  }


}



