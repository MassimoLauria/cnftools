/*
  Copyright (C) 2013 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-07-24, mercoledì 02:15 (CEST) Massimo Lauria"
  Time-stamp: "2013-07-29, 17:00 (CEST) Massimo Lauria"
  
  Description::
  
  Tool to read dimacs clauses in input from a data stream like a file
  or a string.

  The base object is a clause, which is a sequence on
  literals. Literals are represented as integers.
  
*/

// Preamble
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>

#include <vector>
#include <list>

#include <assert.h>
#include <stdexcept>

#include "cnftools.hh"

using namespace std;


template <typename E>
bool parser_throws(const string& data) {
  try {
    parse_dimacs(data);
  } catch(E e) {
    return true;
  } catch(...) {
    return false;
  }
  return false;
}

// Read clauses from input and reprints them
int main(int argc, char *argv[])
{
  cout<<"Hello C++11 world!"<<endl;

  cout<<"Test: data structure"<<endl;
  cnf F;
  F.add_variables(10);
  F.add_clause({1, 2,7 });
  F.add_clause({-5,6,10});
  cout<<F;

  cout<<"Test: parse from file"<<endl;
  ifstream fs {"prova.cnf",ios_base::in};
  cnf G;
  fs>>G;
  cout<<G;


  cout<<"Test: negative variables number"<<endl;
  assert(parser_throws<dimacs_bad_syntax>("p  cnf -1 4"));

  cout<<"Test: negative clauses number"<<endl;
  assert(parser_throws<dimacs_bad_syntax>("p  cnf 1 -4"));

  cout<<"Test: bad formatted spec line"<<endl;
  assert(parser_throws<dimacs_bad_syntax>("p  cnf x 4 4"));

  cout<<"Test: bad running text"<<endl;
  assert(parser_throws<dimacs_bad_syntax>("p  cnf 1 4 asa x 4 4"));

  cout<<"Test: bad clause specification"<<endl;
  assert(parser_throws<dimacs_bad_syntax>("p  cnf 3 4\n 2 3 x 1 0"));

  cout<<"Test: too few clauses"<<endl;
  assert(parser_throws<dimacs_bad_syntax>("p  cnf 3 4\n 2 3 -1 0"));

  cout<<"Test: unexpected end of input"<<endl;
  assert(parser_throws<dimacs_bad_syntax>("p  cnf 3 4\n 2 3 -1 0 2 -1"));

  cout<<"Test: literal referring to non existent variable"<<endl;
  assert(parser_throws<dimacs_bad_value>("p  cnf 3 1\n 4 3 -1 0"));

  cout<<"Test: empty lines"<<endl;
  assert(!parser_throws<dimacs_bad_syntax>("\n\nc comment\n\np  cnf 3 1\n\n\n 4 3 -1 0"));

  cout<<"Test: bad lines"<<endl;
  assert(parser_throws<dimacs_bad_syntax>("\ndfsadssa\nc comment\n\np  cnf 3 1\n\n\n 4 3 -1 0"));

  return 0;
}








