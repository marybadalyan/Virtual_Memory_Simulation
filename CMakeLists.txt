cmake_minimum_required(VERSION 3.10)
project(main CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the output directory for the analysis files
set(ANALYSIS_DIR "${CMAKE_BINARY_DIR}/analysis")
file(MAKE_DIRECTORY ${ANALYSIS_DIR})

add_executable(main main.cpp)
