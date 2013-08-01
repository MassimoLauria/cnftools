/*
  Copyright (C) 2013 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-08-01, giovedì 16:37 (CEST) Massimo Lauria"
  Time-stamp: "2013-08-01, 17:10 (CEST) Massimo Lauria"
  
  Description::
  
  Test suit for the cnf to k-cnf conversion (uses cppunit)

*/

#ifndef _TESTCNF2KCNF_HH_
#define _TESTCNF2KCNF_HH_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class TestCnf2kcnf : public CppUnit::TestFixture  {
  
  CPPUNIT_TEST_SUITE( TestCnf2kcnf );
  // CPPUNIT_TEST( test_even_clause);
  // CPPUNIT_TEST( test_odd_clause);
  // CPPUNIT_TEST( test_small_clause);
  CPPUNIT_TEST( test_to3cnf);
  CPPUNIT_TEST( test_to4cnf);
  // CPPUNIT_TEST( test_to5cnf);
  CPPUNIT_TEST_SUITE_END();
 
public:
  virtual void setUp();
  virtual void tearDown();
  // virtual void test_even_clause();
  // virtual void test_odd_clause();
  // virtual void test_small_clause();
  virtual void test_to3cnf();
  virtual void test_to4cnf();
  // virtual void test_to5cnf();
};

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( TestCnf2kcnf,
                                       "Testing the cnf to k-cnf conversion" );
#endif /* _TESTCNF2KCNF_HH_ */
