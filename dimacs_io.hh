/*
  Copyright (C) 2013 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-08-20, Tuesday 17:18 (CEST) Massimo Lauria"
  Time-stamp: "2013-08-20, 17:49 (CEST) Massimo Lauria"
  
  Description::
  
  Utilities for parsing dimacs files into our cnf data structure.

  A `cnf` data structures can be read from and printed to using I/O
  streams and the standard << >> operators.

  E.g. if F is a cnf object, `cin>>F` parses a dimacs file given to
  the standard input and copies into the object F. To print it back in
  dimacs format just use `cout<<F`
  
  Alteratively a `cnf` object is returned by the `parse_dimacs`
  function, which parse either an input stream or and string.

  For example

     parse_dimacs(cin);

  or

     parse_dimacs("p cnf 2 1\n 1 -2 0"); 

  both return a cnf object.

  Reading from an input stream either with `parse_dimacs` or with the
  >> operator is equivalent, indeed the latter invokes the former. The
  only difference is that `parse_dimacs` can be used for variable
  initialization.

  DIMACS PARSING
  
  A dimacs file is a cnf representation of the following form:

  ---start---
  c Hello this is a comment
  c this is a 3-CNF with three
  c clauses on five variables.
  c
  p cnf 5 3
  -1 3 4 0
  2 5 3 0
  2 1 4 0
  ----end----
  
  The input data may be not correct or bad formatted. If this is the
  case, the parser would throw the following exceptions:

  `dimacs_bad_syntax` (inherit from `std::invalid_argument`)

  Parser throws it when the dimacs file has wrong format. For example
  the spec line indicates a negative number of clauses or of
  variables. Or if it is badly formatted.

  `dimacs_bad_value` (inherit from `std::bad_value`)

  Parser throws it when clauses have unconsistent data with the cnf
  specification. For example when a clause mention literals for
  variables larger than specified at the beginning.

  `dimacs_truncated` (inherit from `std::invalid_argument`)
  
  It is thrown whenever the parser expects either a clause terminator,
  more literals or more clauses and such objects are not present
  (maybe the input reached the end of file).
  
*/

#ifndef _DIMACS_IO_HH_
#define _DIMACS_IO_HH_

#include "cnftools.hh"


// input/output of CNF in dimacs format, using standard iostream operators.
std::istream& operator>>(std::istream &in,cnf& formula);
std::ostream& operator<<(std::ostream &out,const cnf& formula);

// Parse a CNF from a dimacs file, from input stream or from text.
cnf parse_dimacs(std::istream &in);
cnf parse_dimacs(const string &data);


// Parser exceptions
class dimacs_bad_syntax : public std::invalid_argument {
  public:
    dimacs_bad_syntax(const string& data) : std::invalid_argument{data} {}
};

class dimacs_bad_value : public std::domain_error {
  public:
    dimacs_bad_value(const string& data) : domain_error{data} {}
};

class dimacs_truncated : public std::invalid_argument {
  public:
    dimacs_truncated(const string& data) : invalid_argument{data} {}
};



#endif /* _DIMACS_IO_HH_ */
