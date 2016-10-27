cmake_minimum_required(VERSION 3.6)
project(ForEachPerformanceTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    ForEachPerformanceTest.cpp
    stdafx.cpp
    stdafx.h
    targetver.h)

add_executable(ForEachPerformanceTest ${SOURCE_FILES})