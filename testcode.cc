/*
  Copyright (C) 2013 by Massimo Lauria <lauria.massimo@gmail.com>
  
  Created   : "2013-07-29, lunedì 15:47 (CEST) Massimo Lauria"
  Time-stamp: "2013-08-01, 17:03 (CEST) Massimo Lauria"
  
  Description::
  
  Test code for cnftools - it requires cppunit tools (to be installed
  on your system)
  
*/

// Preamble
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

// Tests
#include "testparser.hh"
#include "testcnf2kcnf.hh"

// Code
using namespace std;

int main() {
    CppUnit::TextUi::TestRunner runner;

    runner.addTest(TestDimacsParser::suite());
    runner.addTest(TestCnf2kcnf::suite());

    runner.run();

    return 0;
}
