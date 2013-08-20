/*
  Copyright (C) 2013 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-07-24, mercoledì 02:15 (CEST) Massimo Lauria"
  Time-stamp: "2013-08-20, 15:40 (CEST) Massimo Lauria"
  
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
#include <vector>
#include <string>

#include "cnftools.hh"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;



string documentation = ""
"  Input file is read on STANDARD INPUT and output file is written  \n"
"  on the STANDARD OUTPUT.\n\n" 
"  Tool to read dimacs cnf formula in input and then output a k-CNF \n"
"  version of it.                                                   \n" 
"                                                                   \n" 
"  A clause with more than k literals is transformed in a k-CNF.    \n" 
"                                                                   \n" 
"  e.g. (x1 v x2 v x3 v x4 v x5) and k = 4                          \n" 
"                                                                   \n" 
"  becomes                                                          \n" 
"                                                                   \n" 
"  y_0                                                              \n" 
"  (\\neg y_0 v x1 v x2 v y_1)                                       \n" 
"  (\\neg y_1 v x3 v x4 v y_2)                                       \n" 
"  (\\neg y_2 v x5 v y_3)                                            \n" 
"  \\neg y_3                                                         \n" 
"                                                                   \n" 
"  Given a clause with w literals, each new clause has k-2 original \n" 
"  literals, except for first and last which have up to k-1 original\n"
"  variables.                                                       \n";


void usage(std::ostream &err,string programname) {
  err<<"Usage: "<<programname<<" [-k]"<<endl<<endl;
  err<<"   -k  the width of the output CNF. It is an integer >2 (default k=3)."<<endl;
  err<<endl;
  err<<documentation<<endl;
}


                                                                                 
// Read clauses from input and reprints them
int main(int argc, char *argv[])
{

  size_t target_width {3};

  // process command line options
  vector<string> cmdline(argc);
  copy(argv,argv+argc,cmdline.begin());
  auto arg = cmdline.cbegin();
  
  // check if the first option is a width specification
  if (cmdline.size()>2) {
    usage(cerr,cmdline[0]);
    exit(-1);
  }
  
  arg++;
  if (arg != cmdline.cend() && (*arg)[0]=='-') {
    int value;
    try {

      value = -std::stoi(cmdline[1]);
      if (value < 3) throw std::out_of_range{"The target width must be 3 or more."};
      target_width = value;

    } catch(...) {
      usage(cerr,cmdline[0]);
      exit(-1);
    }
  }
    
  cnf F;
  try {
    cin>>F;
  } catch(dimacs_bad_syntax e) {
    cerr<<"Error in parsing the dimacs input file."<<endl;
    exit(-1);
  } catch(dimacs_truncated e) {
    cerr<<"Unexpected end of input."<<endl;
    exit(-1);
  } catch(dimacs_bad_value e) {
    cerr<<"The CNF formula dimacs file is inconsistent."<<endl;
    exit(-1);
  }

  
  std::cout<<cnf2kcnf(F, target_width);
  
  exit(0);
}
