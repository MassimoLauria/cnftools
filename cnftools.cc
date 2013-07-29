/*
  Copyright (C) 2013 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-07-29, lunedì 16:34 (CEST) Massimo Lauria"
  Time-stamp: "2013-07-29, 16:56 (CEST) Massimo Lauria"
  
  Description::
  
  An implementation of a CNF data structure plus manipulation
  functions, and a DIMACS parser.
  
*/

// Preamble
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "cnftools.hh"

using std::string;
using std::istream;
using std::stringstream;
using std::ostream;
using std::endl;


// Code

void cnf::check_clause_variables(const clause& c) {
  for (literal lit:c) {
    if (lit==null_literal)
      throw dimacs_bad_value{"zero value is not allowed for a literal"};
    if (abs(lit)>varnumber) 
      throw dimacs_bad_value{"a literal refer to non existing variables"};
  }
}
  

// input output facilities for clauses

istream& operator>>(istream &in,clause& c) {
  literal tmp {null_literal};

  c.resize(0);

  while(in >> tmp) {
    if (tmp == null_literal) break;
    c.push_back(tmp);
  }

  if (!in) throw dimacs_bad_syntax{"Bad clause specification in input."};
  if (tmp!=0) throw dimacs_bad_syntax{"Unexpected end of input."};

  return in;
}


ostream& operator<<(ostream &out,const clause& c) {
  if (c.size()>0) out<<c[0];
  for (unsigned int i=1; i < c.size(); ++i) {
    out<<" "<<c[i];
  }
  return out;
}

ostream& operator<<(ostream &out,const cnf& formula) {
  if (formula.size()>0) {
    out<<"p cnf "<<formula.variable_numbers()<<" "<<formula.size()<<endl;
  }
  for (auto c : formula) {
    out<<c<<" 0"<<endl;
  }
  return out;
}

bool only_spaces(const string& data) {
  for (const auto c:data) {
    if (!isspace(c)) return false;
  }
  return true;
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

  // look for the cnf specification line
  while(true) {
    getline(in,buffer);

    if (buffer[0]=='c' || only_spaces(buffer))
      continue;

    else if (buffer[0]=='p')
      break;     

    else
      throw dimacs_bad_syntax{"non comment line before cnf specification."};
  }

  // parse the specification line
  stringstream specline{buffer};

  string spec1 {};
  string spec2 {};
  int n {0}; // variable number
  int m {0}; // clause number

  specline>>spec1>>spec2>>n>>m; // read 'p cnf <nvars> <nclauses>'

  if (!specline || spec1!="p"
      || spec2!="cnf" || n<0 || m < 0)
    throw dimacs_bad_syntax{"Bad specification line:\"p  cnf  <nvars> <nclauses>\" expected."};

  specline>>spec1;
  if (!specline.eof())
    throw dimacs_bad_syntax{"Running characters in the specification line."};

  // read clauses
  cnf    formula {n};
  clause c;
  for (int i=0;i<m;++i) {
    in >> c;
    formula.add_clause(c);
  }
  
  return formula;
}

/* parse a cnf in dimacs format directly form a string */
cnf parse_dimacs(const string &data) {
  stringstream inputdata {data};
  return parse_dimacs(inputdata);
}


istream& operator>>(istream &in,cnf& formula) {
  formula = parse_dimacs(in);
  return in;
}


