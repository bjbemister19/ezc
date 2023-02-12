cmake_minimum_required(VERSION 3.1...3.25)

project(
  ezc
  VERSION 1.0
  LANGUAGES C)

INCLUDE_DIRECTORIES(lib)

set(LIB_SOURCES lib/vec.c
                lib/ezfile.c)

add_executable(testmain app/testmain/main.c ${LIB_SOURCES})
target_link_libraries(testmain)