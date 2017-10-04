cmake_minimum_required(VERSION 3.8)
project(infix_to_postfix_calc)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(infix_to_postfix_calc ${SOURCE_FILES})