cmake_minimum_required(VERSION 3.10)

# set the project name
project(Testfopen)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add the executable
add_executable(testfopen testfopen.c)

set_property(TARGET testfopen PROPERTY C_STANDARD 11)
