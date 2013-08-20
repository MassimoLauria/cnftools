/*
  Copyright (C) 2013 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-08-01, giovedì 16:36 (CEST) Massimo Lauria"
  Time-stamp: "2013-08-20, 19:03 (CEST) Massimo Lauria"
  
  Description::

  Some unit tests for the cnf to k-cnf conversion.
  
*/

// Preamble


#include "testcnf2kcnf.hh"
#include "cnftools.hh"

void TestCnf2kcnf::setUp() {}
void TestCnf2kcnf::tearDown() {}

void TestCnf2kcnf::test_to3cnf()
  {
    cnf a {4};
    a.add_clause({1,2,3,4});
    cnf b {9};
    b.add_clause({5});
    b.add_clause({-5,1,6});
    b.add_clause({-6,2,7});
    b.add_clause({-7,3,8});
    b.add_clause({-8,4,9});
    b.add_clause({-9});
    CPPUNIT_ASSERT_MESSAGE("Conversion to 3 cnf failed",a !=b );
    CPPUNIT_ASSERT_MESSAGE("Conversion to 3 cnf failed",cnf2kcnf(a, 3)==b);

    // // larger formula
    // cnf c { {-1,3,-2,4}, {5,3,-1},
    //         {1,-3,4}, {-1,3,-2,4}};
        
    
    // CPPUNIT_ASSERT_MESSAGE("Conversion to 3 cnf failed",c !=c );
    // CPPUNIT_ASSERT_MESSAGE("Conversion to 3 cnf failed",cnf2kcnf(c, 4)==c);
  }


void TestCnf2kcnf::test_to4cnf()
  {
    cnf a {8};
    a.add_clause({1,2,3,4,5,6,7});
    cnf b {13};
    b.add_clause({9});
    b.add_clause({ -9,1,2,10});
    b.add_clause({-10,3,4,11});
    b.add_clause({-11,5,6,12});
    b.add_clause({-12,7,13});
    b.add_clause({-13});

    CPPUNIT_ASSERT_MESSAGE("Conversion to 3 cnf failed",a !=b );
    CPPUNIT_ASSERT_MESSAGE("Conversion to 3 cnf failed",cnf2kcnf(a, 4)==b);
  }
