/*
  Copyright (C) 2013 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-07-29, lunedì 16:35 (CEST) Massimo Lauria"
  Time-stamp: "2013-08-20, 17:39 (CEST) Massimo Lauria"
  
  Description::
  
  CNF tools includes a library to manage propositional formulas in CNF
  form. In particular here we define a data structure for CNFs, plus
  some manipulation tools and a parser for dimacs files.

  CNFs can be read/written from dimacs files using standard << and <<
  operator for iostream.  Dimacs clauses can be also parsed in input
  from a data stream like a file or a string.

  A CNF is basically a list of clauses. A clause is a sequence on
  literals. Literals are represented as integers.

*/

#include <vector>
#include <list>
#include <stdexcept>
#include <iostream>
#include <string>
#include <algorithm>
#include <assert.h>

#ifndef _CNFTOOLS_HH_
#define _CNFTOOLS_HH_

// Code

using literal  = int;
using variable = int;
using clause = std::vector<literal>;

const literal null_literal {0};

constexpr literal toliteral(const variable& v,bool sign) {
  return static_cast<literal>(v)*(sign?1:-1);
}

using std::string;
using std::list;
using std::vector;
using std::initializer_list;
using std::max;


// parser exceptions


class cnf {

  private:

    variable varnumber;
    std::list<clause> clauses;
  
  public:

    using size_type = typename std::list<clause>::size_type;
    using clause_iterator = typename std::list<clause>::const_iterator;
    
    clause_iterator begin() const { return clauses.begin(); }
    clause_iterator end()   const { return clauses.end(); }
  
    
    cnf(variable nvars=0):
      varnumber {nvars},
      clauses{} {
        if (nvars<0)
          throw std::invalid_argument{"Number of variable must be non negative."};}
    
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
    
    cnf(cnf&& rvalue):
      varnumber{rvalue.varnumber},
      clauses {std::move(rvalue.clauses)}
    { }
    
    cnf(cnf&  value):
      varnumber{value.varnumber},
      clauses  {value.clauses}
    { }
    
    cnf(const std::initializer_list<clause>& clauses);
  
    variable variables_number() const {return varnumber;}
    
    void update_variables(variable atleast) {
      varnumber = std::max(atleast,varnumber);
    }
  
    variable add_variable() {
      return ++varnumber;
    }

    // A clause is added to the cnf. The clause is checked for sanity
    // before any change is done to the cnf object. If clause is
    // consistent and mentions new variables, the number of variables
    // is raised in the cnf object.
    void add_clause(const clause& c) {

      variable newvars {0};

      for (literal lit:c) {
        if (lit==null_literal)
          throw std::domain_error{"zero value is not allowed for a literal"};
        newvars = max(abs(lit),newvars);
      }
      update_variables(newvars);
      clauses.push_back(c);
    }
    
    size_type size() const { return clauses.size(); }

    bool operator==(const cnf& other) const;
    bool operator!=(const cnf& other) const { return !((*this)==other);};

  };
  


#include "dimacs_io.hh"  // cnf I/O in dimacs format.


/* CNF manipulation */
cnf cnf2kcnf(const cnf& F,size_t k);



#endif /* _CNFTOOLS_HH_ */
