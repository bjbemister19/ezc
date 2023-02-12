cmake_minimum_required(VERSION 3.1...3.25)

project(
  ezc
  VERSION 1.0
  LANGUAGES C)

INCLUDE_DIRECTORIES(lib)

set(SOURCES lib/vec.c
            lib/ezfile.c
            main/main.c)

add_executable(testmain  ${SOURCES})
target_link_libraries(testmain)