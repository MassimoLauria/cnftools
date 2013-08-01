/*
  Copyright (C) 2013 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-07-24, mercoledì 02:15 (CEST) Massimo Lauria"
  Time-stamp: "2013-08-01, 16:27 (CEST) Massimo Lauria"
  
  Description::
  
  Tool to read dimacs cnf formula in input and then output a k-CNF
  version of it.

  A clause with more than k literals is transformed in a k-CNF.

  e.g. (x1 v x2 v x3 v x4 v x5) and k = 4

  becomes

  y_0
  (\neg y_0 v x1 v x2 v y_1)
  (\neg y_1 v x3 v x4 v y_2)
  (\neg y_2 v x5 v y_3)
  \neg y_3

  Given a clause with w literals, each new clause has k-2 original
  literals, except for first and last which have up to k-1 original
  variables.
*/

// Preamble
#include <cstdlib>
#include <iostream>

#include "cnftools.hh"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

// Read clauses from input and reprints them
int main(int argc, char *argv[])
{
  cnf F;
  try {
    cin>>F;
  } catch(dimacs_bad_syntax e) {
    cerr<<"Error in parsing the dimacs input file."<<endl;
    exit(-1);
  } catch(dimacs_bad_value e) {
    cerr<<"The CNF formula dimacs file is inconsistent."<<endl;
    exit(-1);
  }

  
  std::cout<<cnf2kcnf(F, 3);
  
  exit(0);
}
