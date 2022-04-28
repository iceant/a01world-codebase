cmake_minimum_required(VERSION 3.0)
project(a01world C)

include_directories(.)

add_library(aw01world aw_types.c aw_memory.c aw_vector.c aw_hexdump.c aw_hexdump.h aw_hashtable.c)

include(Test.cmake)