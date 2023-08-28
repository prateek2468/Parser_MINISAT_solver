#ifndef SAT_H
#define SAT_H

#include <vector>
#include <iostream>
#include <memory>
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"

bool satCallingMiniSat(unsigned int numVar, std::vector<std::vector<int> > &cnf); // return the SAT result of cnf by calling MiniSAT

#endif
