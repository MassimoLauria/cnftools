/*
  Copyright (C) 2013 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-07-29, lunedì 16:11 (CEST) Massimo Lauria"
  Time-stamp: "2013-07-29, 16:31 (CEST) Massimo Lauria"
  
  Description::
  
  Test the dimacs parser code
  
*/

// Preamble
#include <cppunit/extensions/HelperMacros.h>

#include "testparser.hh"

using namespace std;

void TestDimacsParser::setUp() {}
void TestDimacsParser::tearDown() {}

void TestDimacsParser::testEquality()
  {
    CPPUNIT_ASSERT( 1 == 2 );
    CPPUNIT_ASSERT( !(1 == 1) );
  }

void TestDimacsParser::testAddition()
  {
    CPPUNIT_ASSERT( 2+1 == 2 );
  }

