cmake_minimum_required(VERSION 3.0)
project(a01world C)

include_directories(.)

add_library(aw01world aw_types.c)

include(Test.cmake)