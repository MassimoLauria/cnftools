/*
  Copyright (C) 2013 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-07-29, lunedì 16:34 (CEST) Massimo Lauria"
  Time-stamp: "2013-08-20, 17:56 (CEST) Massimo Lauria"
  
  Description::
  
  An implementation of a CNF data structure plus manipulation
  functions, and a DIMACS parser.
  
*/

// Preamble
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <locale>

#include "cnftools.hh"

using std::string;
using std::istream;
using std::stringstream;
using std::ostream;
using std::endl;
using std::isdigit;

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



//
// Utility for CNF manipulations
//


// convert a cnf with into an equisatisfiable k-cnf using extension
// variables.
cnf cnf2kcnf(const cnf& F,size_t k) {

  if (k<3) {
    throw std::invalid_argument{
      "it is not possible to convert a general cnf into a 2-CNF."};}
  
  variable extension {0};
  
  cnf G {F.variables_number()};
 
  for(const auto& cla: F) {

    // small clauses are copied
    if (cla.size()<=k) {

      G.add_clause(cla);
      continue;
      
    } else  {

      // clauses have k-2 original (less for the last one) variables
      // plus an extension variable at the beginning and one at the
      // end.  The first literal is the negation to the last of the
      // previous clause.
      clause tempclause {};

      for(size_t i=0; i<cla.size(); ++i) {

        // close previous clause and open a new one
        if (i % (k-2)==0) {

          extension=G.add_variable();
          tempclause.push_back(toliteral(extension, true));
          G.add_clause(tempclause);

          tempclause.resize(0);
          tempclause.push_back(toliteral(extension, false));
        }
        
        tempclause.push_back(cla[i]);

      }

      // close the open clause
      extension=G.add_variable();
      tempclause.push_back(toliteral(extension, true));
      G.add_clause(tempclause);

      // last clause is just a single extension literal
      tempclause.resize(0);
      tempclause.push_back(toliteral(extension, false));
      G.add_clause(tempclause);
      
        
    }
    
  }

  return G;
}
