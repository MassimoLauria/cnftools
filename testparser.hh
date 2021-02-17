/*
  Copyright (C) 2013, 2021 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-07-29, lunedì 16:19 (CEST) Massimo Lauria"
  Time-stamp: "2021-02-17, 01:36 (CET) Massimo Lauria"
  
  Description::
  
  Test suit for the dimacs parser (uses cppunit)
  
*/

#ifndef _TESTPARSER_HH_
#define _TESTPARSER_HH_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class TestDimacsParser : public CppUnit::TestFixture  {
  
  CPPUNIT_TEST_SUITE( TestDimacsParser );
  CPPUNIT_TEST( spec_line_parse );
  CPPUNIT_TEST( read_clauses );
  CPPUNIT_TEST_SUITE_END();
 
public:
  virtual void setUp();
  virtual void tearDown();
  virtual void spec_line_parse();
  virtual void read_clauses();
};
#endif /* _TESTPARSER_HH_ */








