/*
  Copyright (C) 2013 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-07-29, lunedì 16:35 (CEST) Massimo Lauria"
  Time-stamp: "2013-08-01, 17:18 (CEST) Massimo Lauria"
  
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


// parser may throw exceptions on parsing errors 
class dimacs_bad_syntax : public std::invalid_argument {

public:
dimacs_bad_syntax(const string data) : std::invalid_argument{data} {}
};

class dimacs_bad_value : public std::domain_error {
public:
dimacs_bad_value(const string data) : domain_error{data} {}
};



class cnf {

  private:

    variable varnumber;
    std::list<clause> clauses;
    
    void check_clause_variables(const clause& c);
    
  public:
    
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
    
    cnf(vector<clause>& clauses);
  
    variable variable_numbers() const {return varnumber;}
    
    void add_variables(variable n) {
      if (n<0)
        throw std::invalid_argument{"Number of new variable must be non negative."};
      varnumber += n;
    }
  
    variable add_variable() {
      return ++varnumber;
    }

    void add_clause(const clause& c) {
      check_clause_variables(c);
      clauses.push_back(c);
    }
    
    size_t size() const { return clauses.size(); }

    bool operator==(const cnf& other) const;
    bool operator!=(const cnf& other) const { return !((*this)==other);};

  };
  

// input output facilities for clauses
std::istream& operator>>(std::istream &in,clause& c);
std::ostream& operator<<(std::ostream &out,const clause& c);
std::ostream& operator<<(std::ostream &out,const cnf& formula);



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
cnf parse_dimacs(std::istream &in);
std::istream& operator>>(std::istream &in,cnf& formula);


/* parse a dimacs cnf file from a string */
cnf parse_dimacs(const string &data);


/* CNF manipulation */
cnf cnf2kcnf(const cnf& F,size_t k);


#endif /* _CNFTOOLS_HH_ */
