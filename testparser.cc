/*
  Copyright (C) 2013 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-07-29, lunedì 16:11 (CEST) Massimo Lauria"
  Time-stamp: "2013-07-29, 17:54 (CEST) Massimo Lauria"
  
  Description::
  
  Test the dimacs parser code
  
*/

// Preamble
//#include <cppunit/extensions/HelperMacros.h>

#include "testparser.hh"

#include "cnftools.hh"

template <typename E>
static bool parser_throws(const string& data) {
  try {
    parse_dimacs(data);
  } catch(E e) {
    return true;
  } catch(...) {
    return false;
  }
  return false;
}

void TestDimacsParser::setUp() {}
void TestDimacsParser::tearDown() {}

void TestDimacsParser::spec_line_parse()
  {
    CPPUNIT_ASSERT_MESSAGE("Parser must fail on negative number of variables",
                           parser_throws<dimacs_bad_syntax>("p  cnf -1 4"));
    CPPUNIT_ASSERT_MESSAGE("Parser must fail on negative number of clauses",
                           parser_throws<dimacs_bad_syntax>("p  cnf 1 -4"));
    CPPUNIT_ASSERT_MESSAGE("Parser must fail on bad spec line",
                           parser_throws<dimacs_bad_syntax>("p  cnf x 4 4"));
    CPPUNIT_ASSERT_MESSAGE("Spec line is on a single line and has not other data.",
                           parser_throws<dimacs_bad_syntax>("p  cnf 1 4 asa x 4 4"));
    CPPUNIT_ASSERT_MESSAGE("Spec line is on a single line and has not other data.",
                           parser_throws<dimacs_bad_syntax>("p  cnf\n 1 1\n 1 0"));
  }


void TestDimacsParser::read_clauses() {
  CPPUNIT_ASSERT_MESSAGE("A clause is alwyas a sequence of integers",
                         parser_throws<dimacs_bad_syntax>("p  cnf 3 4\n 2 3 x 1 0"));
  CPPUNIT_ASSERT_MESSAGE("Test for missing clauses",
                         parser_throws<dimacs_bad_syntax>("p  cnf 3 4\n 2 3 -1 0"));
  CPPUNIT_ASSERT_MESSAGE("Unexpected end of input",
                         parser_throws<dimacs_bad_syntax>("p  cnf 3 4\n 2 3 -1 0 2 -1"));
  CPPUNIT_ASSERT_MESSAGE("Literal referring to non existent variable in the CNF",
                         parser_throws<dimacs_bad_value>("p  cnf 3 1\n 4 3 -1 0"));
}
