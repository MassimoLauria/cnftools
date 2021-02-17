/*
  Copyright (C) 2013, 2021 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-08-01, giovedì 17:31 (CEST) Massimo Lauria"
  Time-stamp: "2021-02-17, 01:36 (CET) Massimo Lauria"
  
  
*/

// Preamble

#include "testbasic.hh"
#include "cnftools.hh"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( TestBasic,
                                       "Testing CNF object implementation" );



using namespace std;


void TestBasic::setUp() {}
void TestBasic::tearDown() {}

void TestBasic::test_list_constructor() {
  cnf a {5};
  a.add_clause({-1,3,-2,4});
  a.add_clause({5,3,-1});
  a.add_clause({1,-3,4});
  a.add_clause({1,3,2,5});
  
  // initilized with list
  cnf b { {-1, 3,-2,4},
          { 5, 3,-1},
          { 1,-3, 4},
          { 1, 3, 2,5}};
  
  // different order
  cnf c {  {5,3,-1},{1,3,2,5},
           {1,-3,4}, {-1,3,-2,4}};
  
  CPPUNIT_ASSERT_MESSAGE("Explicit vs init-list constructor",a==b);
  CPPUNIT_ASSERT_MESSAGE("CNF and clauses are ordered sequences",a!=c);
  CPPUNIT_ASSERT_MESSAGE("Different order must cause different cnf objects",b!=c);
}


void TestBasic::test_clause_addition() {
  cnf a {2};
  a.add_clause({1,-2});
  CPPUNIT_ASSERT(a.variables_number()==2);
  a.add_clause({1,2,-4,5});
  CPPUNIT_ASSERT(a.variables_number()==5);
  CPPUNIT_ASSERT_THROW(a.add_clause({-6,1,0,5}),std::domain_error); // do not work well on MacOSX
  CPPUNIT_ASSERT_MESSAGE("Clause addition which raise an exception must be rolled back",a.variables_number()==5);
}

