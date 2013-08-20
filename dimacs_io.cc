/*
  Copyright (C) 2013 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-08-20, Tuesday 17:17 (CEST) Massimo Lauria"
  Time-stamp: "2013-08-20, 19:00 (CEST) Massimo Lauria"
  
  Description::
  
  Code for cnf formula I/O in dimacs format.

  Implementation file: see the header file `dimacs_io.hh` for actual
  documentation.
  
*/

// Preamble
#include "cnf.hh"
#include "dimacs_io.hh"

// 
#include <iostream>
#include <sstream>
#include <locale>

using std::string;
using std::istream;
using std::stringstream;
using std::ostream;
using std::endl;
using std::isdigit;


// Code

// standard input/output iostream operator for clauses, implemented
// for internal use only.
//
// if the clause in input is bad formatted, or the input ends
// unexpectedly an exception is thrown. The parser should propagate it
// upward.

static istream& operator>>(istream &in,clause& c) {

  literal tmp {null_literal};
  bool    endofclause {false};

  c.resize(0);

  while(in >> tmp) {
    if (tmp == null_literal) {endofclause=true; break; }
    c.push_back(tmp);
  }

  if (in.eof() && !endofclause) throw dimacs_truncated{"Unexpected end of clause."};
  if (in.fail()) throw dimacs_bad_syntax{"Bad clause specification in input."};

  return in;
}

static ostream& operator<<(ostream &out,const clause& c) {
  if (c.size()>0) out<<c[0];
  for (unsigned int i=1; i < c.size(); ++i) {
    out<<" "<<c[i];
  }
  return out;
}


// standard input/output iostream operator for cnf
//
// the cnf is printed and read in dimacs format.

ostream& operator<<(ostream &out,const cnf& formula) {
  out<<"p cnf "<<formula.variables_number()<<" "<<formula.size()<<endl;
  for (auto c : formula) {
    out<<c<<" 0"<<endl;
  }
  return out;
}

istream& operator>>(istream &in,cnf& formula) {
  formula = parse_dimacs(in);
  return in;
}




// Utility function for testing characters in string
static bool only_spaces(const string& data) {
  for (const auto c:data) {
    if (!isspace(c)) return false;
  }
  return true;
}


static bool only_digits(const string& data) {
  for(const auto c: data) {
    if (!isdigit(c)) return false;
  } 
  return true;
}


/* Parse a dimacs file given as an input stream */
cnf parse_dimacs(istream &in) {
  
  string buffer {};

  // looks for the cnf specification line, and ignore comments and
  // empty lines preceding it.
  while(true) {
    getline(in,buffer);

    if (buffer[0]=='c' || only_spaces(buffer))
      continue;

    else if (buffer[0]=='p')
      break;     

    else
      throw dimacs_bad_syntax{"non comment line before cnf specification."};
  }

  // parse the specification line of the form 'p cnf n m'
  stringstream specline{buffer};

  string s_p   {};
  string s_cnf {};
  string s_n   {};
  string s_m   {};
  
  variable n {0};        // variable number
  cnf::size_type m {0};  // clause number 

  specline>>s_p>>s_cnf>>s_n>>s_m; // parse the spec line
  
  if (specline.fail() ||
      s_p!="p" || s_cnf!="cnf" ||
      !only_digits(s_n) || !only_digits(s_m)) {
    throw dimacs_bad_syntax{"Bad specification line: \"p  cnf  <nvars> <nclauses>\" expected."};
  } 

  // we verified that s_n and s_m are sequence of just digits, so they
  // represent positive integers. We need to do this passage
  // explicitly because C++ standard I/O system do not check if signed
  // integer is read into an unsigned integer.
  (stringstream {s_n})>>n;
  (stringstream {s_m})>>m;

  specline>>s_p;
  if (!specline.eof())
    throw dimacs_bad_syntax{"Running characters in the specification line."};
  
  // read clauses
  cnf    formula {n};
  clause c;
  for (size_t i=0;i<m;++i) {
    in >> c;
    formula.add_clause(c);
    if (formula.variables_number() > n)
      throw dimacs_bad_value{"Dimacs file contains clauses with invalid literals."};
  }
  
  return formula;
}

/* parse a cnf in dimacs format directly from a string */
cnf parse_dimacs(const string &data) {
  stringstream inputdata {data};
  return parse_dimacs(inputdata);
}


