/*
  Copyright (C) 2013 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-07-24, mercoledì 02:15 (CEST) Massimo Lauria"
  Time-stamp: "2013-07-29, 18:51 (CEST) Massimo Lauria"
  
  Description::
  
  Tool to read dimacs cnf formula in input and then output a 3-CNF
  version of it.

  A clause with more than three literals is transformed in a 3-CNF.

  e.g. (x1 v x2 v x3 v x4)

  becomes

  y_0
  (\neg y_0 v x1 v y_1)
  (\neg y_1 v x2 v y_2)
  (\neg y_2 v x3 v y_3)
  (\neg y_3 v x4 v y_4)
  \neg y_4
  
*/

// Preamble
#include <cstdlib>
#include <iostream>

#include "cnftools.hh"

using namespace std;


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

  // this estimates the number of variables for the new formula a
  // clause with less than four literals is left untouched.  any other
  // is converted.
  int total=F.variable_numbers();
  for(const auto& cla: F) {
    if (cla.size()>3)
      total += cla.size()+1;
  }

  cnf G {total};
  literal n = F.variable_numbers();

  for(const auto& cla: F) {

    // small clauses are copied
    if (cla.size()<=3) {
      G.add_clause(cla);
      continue;
    }

    // large ones are converted
    ++n;
    G.add_clause({n});
    for (auto lit: cla) {
      G.add_clause({-n,lit,++n});
    }
    G.add_clause({-n});
  }
  
  cout<<G;
  
  exit(0);
}
