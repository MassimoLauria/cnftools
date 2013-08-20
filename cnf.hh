/*
  Copyright (C) 2013 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-08-20, Tuesday 18:37 (CEST) Massimo Lauria"
  Time-stamp: "2013-08-20, 18:55 (CEST) Massimo Lauria"
  
  Description::
  
  Data structure for CNF formulas.
  
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
