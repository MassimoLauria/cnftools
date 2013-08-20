/*
  Copyright (C) 2013 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-07-29, lunedì 16:35 (CEST) Massimo Lauria"
  Time-stamp: "2013-08-20, 18:53 (CEST) Massimo Lauria"
  
  Description::
  
  CNF tools includes a library to manage propositional formulas in CNF
  form. In particular here we define a data structure for CNFs, plus
  some manipulation tools and a parser for dimacs files.

  A CNF is basically a list of clauses. A clause is a sequence on
  literals. Literals are represented as integers.

  CNFs can be read/written from dimacs files using standard << and <<
  operator for iostream.  Dimacs clauses can be also parsed in input
  from a data stream like a file or a string.

  Documentation for cnf data structure and for parsers is in the
  relative header files.
*/


#ifndef _CNFTOOLS_HH_
#define _CNFTOOLS_HH_


#include "cnf.hh"        // cnf data structure
#include "dimacs_io.hh"  // cnf I/O in dimacs format.


/* CNF manipulation tools */
cnf cnf2kcnf(const cnf& F,size_t k);


#endif /* _CNFTOOLS_HH_ */
