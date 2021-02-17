cmake_minimum_required(VERSION 3.10)

project(cnf2kcnf)

include_directories(
    ${CPPUNIT_INC}
)
link_directories(
    ${CPPUNIT_LIB}
)

add_executable(cnf2kcnf
  cnf2kcnf.cc
  cnf.cc
  dimacs_io.cc
  cnftools.cc
  )

add_executable(testcode
  testcode.cc
  testbasic.cc
  testparser.cc
  testcnf2kcnf.cc
  cnf.cc
  dimacs_io.cc
  cnftools.cc
  )

target_link_libraries(
    testcode
    cppunit
)
INSTALL(TARGETS testcode DESTINATION ${PROJECT_OUTPUT_TEST_DIR})
ADD_TEST(NAME testcode COMMAND "${PROJECT_OUTPUT_TEST_DIR}/testcode")
