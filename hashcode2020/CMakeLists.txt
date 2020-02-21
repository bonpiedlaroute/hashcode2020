cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_COMPILER /usr/local/bin/gcc-7)
set(CMAKE_CXX_COMPILER /usr/local/bin/g++-7)

# set the project name
project(hashcode)

set(CMAKE_CXX_STANDARD 11)

add_executable(hashcode scan.cpp)
