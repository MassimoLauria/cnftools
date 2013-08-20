/*
  Copyright (C) 2013 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-08-20, Tuesday 18:36 (CEST) Massimo Lauria"
  Time-stamp: "2013-08-20, 18:51 (CEST) Massimo Lauria"
  
  Description::
  
  Class for CNF formulas. Documentation is in the corresponding header file.
  
*/

// Preamble

#include <initializer_list>

#include "cnf.hh"

// Code
cnf::cnf(const std::initializer_list<clause>& clauses): varnumber {0}, clauses {} {
  for (auto& cla : clauses) {
    add_clause(cla);    
  }
}

bool cnf::operator==(const cnf& other) const {
  if (variables_number()!= other.variables_number()) return false;

  return clauses==other.clauses;
}


