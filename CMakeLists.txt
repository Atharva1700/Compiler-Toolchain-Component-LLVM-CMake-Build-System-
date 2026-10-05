cmake_minimum_required(VERSION 3.10)
project(SimpleIRAnalysisPass)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find LLVM
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Build the pass
add_library(SimpleAnalysisPass MODULE src/SimpleAnalysisPass.cpp)
target_link_libraries(SimpleAnalysisPass ${LLVM_LIBS})

# Test: compile a simple C file to IR
add_custom_target(test_ir
  COMMAND clang -emit-llvm -c ${CMAKE_CURRENT_SOURCE_DIR}/test/simple.c -o ${CMAKE_CURRENT_BINARY_DIR}/simple.bc
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test/simple.c
)

# Run the pass
add_custom_target(run_pass
  COMMAND opt -load-pass-plugin ${CMAKE_CURRENT_BINARY_DIR}/libSimpleAnalysisPass.so -passes=simple-analysis ${CMAKE_CURRENT_BINARY_DIR}/simple.bc -o /dev/null
  DEPENDS SimpleAnalysisPass test_ir
)
