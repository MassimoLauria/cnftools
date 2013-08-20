/*
  Copyright (C) 2013 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-08-20, Tuesday 18:37 (CEST) Massimo Lauria"
  Time-stamp: "2013-08-20, 19:37 (CEST) Massimo Lauria"
  
  Description::
  
  Data structure for CNF formulas.

  Given n boolean variables (i.e with true/false values), a cnf
  formula is a conjunction of clauses, which are disjunctions made of
  variables and negated variables.

  More precisely a literal is either a variable X of the negation NOT
  X. A clause is the logical OR of several literals, and a CNF is the
  logical AND of several clauses.
  

  Variables for a CNF formula of n variables are indexed from 1 to n,
  and the indices are identified with the boolean variables.  A
  positive (resp. negative) literal on variable `v` is represented by
  the value `v` itself (resp. the value `-v`).

  Notice that this representation is exactly the same of dimacs format
  for CNFs.
  
  Variables indices have type `variable` while literals have type
  `literals`. Notice that `variable` is a signed type and `literal` is
  just an alias for that.
    
  Each clause is represented as a standard C++ vector of literals and
  the CNF as a standard C++ list of clauses.

  The `cnf` object can indeed be iterated with read/only access as a
  list of vector<literal>, each representing a clause.

  N.B.: literals and clauses order matter. Comparison by value takes
  order in consideration to decide if two `cnf` objects are the same.

  Constructing and object:

  1. empty object
  
     cnf F;
     F.add_clause({-1,2,3});

     cnf F{5};
     F.add_clause({-1,2,3});

     the number of variable may or may not be specified. If not is 0
     by default. Every time a clause is added, the number of variables
     may be increased to accomodate for new literals.

     cnf F{3}
     F.add_clause({-1,2});
     F.variable_number();  // it returns 3
     F.add_clause({-1,2,5});
     F.variable_number();  // it returns 5
         
  2. copy

     cnf G {F};

  3. initializer list

     cnf F{{1,2,-3}{2,5,-1},{1,-4,-5},{}}; // formula contains the empty clause!
 
  Implementation note:

  1 . the C++11 move semantic has been implemented in order to have an
  efficient to manage objects by value without using pointer.

  2 . literal, variable, clause types are just aliases to library
  types, so the type system do not distinguish between the alias and
  the original type.
  
*/

#ifndef _CNF_HH_
#define _CNF_HH_

#include <vector>
#include <list>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>


// Code

using literal  = int;
using variable = int;
using clause = std::vector<literal>;

const literal null_literal {0};

constexpr literal toliteral(const variable& v,bool sign) {
  return static_cast<literal>(v)*(sign?1:-1);
}


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
        newvars = std::max(abs(lit),newvars);
      }
      update_variables(newvars);
      clauses.push_back(c);
    }
    
    size_type size() const { return clauses.size(); }

    bool operator==(const cnf& other) const;
    bool operator!=(const cnf& other) const { return !((*this)==other);};

  };


#endif /* _CNF_HH_ */
