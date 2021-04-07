
include(${PROJECT_SOURCE_DIR}/cmake/FetchGTest.cmake)

set(ENDN_TESTS_TARGET "${ENDN_TARGET}Tests")

set(ENDN_TESTS_SRCS
  Tests.cpp
  BigTests.cpp
  LittleTests.cpp
)

message(STATUS "Add Test: ${ENDN_TESTS_TARGET}")

add_executable(${ENDN_TESTS_TARGET} ${ENDN_TESTS_SRCS})
target_link_libraries(${ENDN_TESTS_TARGET} PRIVATE
  ${ENDN_TARGET}
  gtest
  gmock
)
set_target_properties(${ENDN_TESTS_TARGET} PROPERTIES FOLDER "Tests")

add_test(NAME ${ENDN_TESTS_TARGET} COMMAND ${ENDN_TESTS_TARGET})
