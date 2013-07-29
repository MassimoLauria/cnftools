/*
  Copyright (C) 2013 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-07-29, lunedì 16:19 (CEST) Massimo Lauria"
  Time-stamp: "2013-07-29, 16:28 (CEST) Massimo Lauria"
  
  Description::
  
  Test suit for the dimacs parser (uses cppunit)
  
*/

#ifndef _TESTPARSER_HH_
#define _TESTPARSER_HH_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class TestDimacsParser : public CppUnit::TestFixture  {

  CPPUNIT_TEST_SUITE( TestDimacsParser );
  CPPUNIT_TEST( testAddition );
  CPPUNIT_TEST( testEquality );
  CPPUNIT_TEST_SUITE_END();

  
public:
  virtual void setUp();
  virtual void tearDown();
  virtual void testEquality();
  virtual void testAddition();
};

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( TestDimacsParser, "Testing the dimacs parser" );
#endif /* _TESTPARSER_HH_ */
