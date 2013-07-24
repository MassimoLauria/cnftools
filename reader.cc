/*
  Copyright (C) 2013 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-07-24, mercoledì 02:15 (CEST) Massimo Lauria"
  Time-stamp: "2013-07-24, 19:33 (CEST) Massimo Lauria"
  
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

// #include "reader.h"

using namespace std;

// Code
using literal  = int;
using variable = literal;
using clause = std::vector<literal>;
 
const literal null_literal {0};


class cnf {

private:

  int  varnumber;
  list<clause> clauses;

  void check_clause_variables(const clause& c) {
    for (literal lit:c) {
      if (lit==null_literal) 
        throw domain_error{"clauses are not supposed to contain a zero value"};
      if (abs(lit)>varnumber) 
        throw domain_error{"a literal refer to non existing variables"};
    }
  }
  
public:

  using clause_iterator = typename list<clause>::const_iterator;

  clause_iterator begin() const { return clauses.begin(); }
  clause_iterator end()   const { return clauses.end(); }
  
  
  cnf(int nvars=0):
    varnumber {nvars},
    clauses{} {}

  cnf& operator=(cnf&& rvalue) {
    varnumber    = rvalue.varnumber;
    clauses = std::move(rvalue.clauses);
    return *this;
  }

  cnf& operator=(cnf&  value) {
    varnumber = value.varnumber;
    clauses = value.clauses;
    return *this;
  }

  cnf(cnf&& rvalue) {
    varnumber    = rvalue.varnumber;
    clauses = std::move(rvalue.clauses);
  }
  
  cnf(cnf& value) {
    varnumber = value.varnumber;
    clauses = value.clauses;
  }
  
  size_t variable_numbers() const {return varnumber;}
  
  void add_variables(size_t n) {
    varnumber += n;
  }

  void add_clause(const clause& c) {
    check_clause_variables(c);
    clauses.push_back(c);
  }

  size_t size() const { return clauses.size(); }
};

istream& operator>>(istream &in,clause& c) {
  literal tmp {null_literal};

  c.resize(0);

  while(in >> tmp) {
    if (tmp == null_literal) break; 
    c.push_back(tmp);
  }
  return in;
}


ostream& operator<<(ostream &out,const clause& c) {
  if (c.size()>0) cout<<c[0];
  for (unsigned int i=1; i < c.size(); ++i) {
    out<<" "<<c[i];
  }
  return out;
}

ostream& operator<<(ostream &out,const cnf& formula) {
  if (formula.size()>0) {
    cout<<"p cnf "<<formula.variable_numbers()<<" "<<formula.size()<<endl;
  }
  for (auto c : formula) {
    out<<c<<" 0"<<endl;
  }
  return out;
}

/* Parse a dimacs file, which is a cnf representation of the following
   form:
   
c Hello this is a comment
c this is a 3-CNF with three
c clauses on five variables.
c
p cnf 5 3
-1 3 4 0
2 5 3 0
2 1 4 0
*/
cnf parse_dimacs(istream &in) {

  string buffer {};
  string bufferaux {};
  bool   still_reading {false};

  // look for the cnf specification line
  while(true) {
    getline(in,buffer);

    if (still_reading)
      continue;
    
    if (buffer[0]=='c')
      continue;

    else if (buffer[0]=='p')
      break;     

    else
      throw invalid_argument {"non comment line before cnf specification."};
  }

  // parse the specification line
  stringstream specline{buffer};
  specline>>bufferaux;
  assert(bufferaux=="p");
  specline>>bufferaux;
  assert(bufferaux=="cnf");

  int n {0}; // variable number
  int m {0}; // clause number

  specline>>n;
  specline>>m;

  // read clauses
  cnf    formula {n};
  clause c;
  for (int i=0;i<m;++i) {
    in >> c;
    formula.add_clause(c);
  }
  
  return formula;
}


// Read clauses from input and reprints them
int main(int argc, char *argv[])
{
  cout<<"Hello C++11 world!"<<endl;

  cnf F;
  F.add_variables(10);
  F.add_clause({1, 2,7 });
  F.add_clause({-5,6,10});
  
  cout<<F;

  ifstream fs {"prova.cnf",ios_base::in};
  
  cnf G=parse_dimacs(fs);
  cout<<G;
  
  return 0;
}

