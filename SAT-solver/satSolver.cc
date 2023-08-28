#include "satSolver.h"
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
#include <iostream>
#include <memory>

bool satCallingMiniSat(unsigned int numVar, std::vector<std::vector<int> > &cnf) {
  // your code starts here

  
  std::unique_ptr<Minisat::Solver > solver(new Minisat::Solver());
  Minisat::Lit arr[numVar ];

  for (int i = 1; i <= numVar; i++){
    arr[i] =  Minisat::mkLit(solver->newVar());; 
  }
  
  for (int i = 0; i < cnf.size(); i++){ 
    Minisat::vec<Minisat::Lit> SomeVector;
    int num1 ; 
    for (int j = 0; j < cnf[i].size(); j++)
    {
      int num = cnf[i][j];
      num1 = num ; 
       if(num>0){
       SomeVector.push(arr[num]);
       }else{
         SomeVector.push(~arr[(num) * (-1)  ]);
       } 
       
     }
     solver->addClause(SomeVector);
     SomeVector.clear() ; 
     
  }
  bool result = solver->solve() ; 
  solver.reset (new Minisat::Solver());
  return result;

}
