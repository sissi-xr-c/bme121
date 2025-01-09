cmake_minimum_required(VERSION 3.29)
project(assignment5)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(assignment5
    processStudents.cpp
    processStudents.h
    processStudentsSampleMain.cpp)
