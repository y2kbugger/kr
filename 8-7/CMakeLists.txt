cmake_minimum_required(VERSION 3.10)

# set the project name
project(malloc)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# add the executable
add_executable(malloc malloc.c)

set_property(TARGET malloc PROPERTY C_STANDARD 11)


enable_testing()

# does the application run
add_test(NAME Runs COMMAND malloc)

# More examples

# # does the usage message work?
# add_test(NAME Usage COMMAND Tutorial)
# set_tests_properties(Usage
#   PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number"
#   )

# # define a function to simplify adding tests
# function(do_test target arg result)
#   add_test(NAME Comp${arg} COMMAND ${target} ${arg})
#   set_tests_properties(Comp${arg}
#     PROPERTIES PASS_REGULAR_EXPRESSION ${result}
#     )
# endfunction(do_test)

# # do a bunch of result based tests
# do_test(Tutorial 4 "4 is 2")
# do_test(Tutorial 9 "9 is 3")
# do_test(Tutorial 5 "5 is 2.236")
# do_test(Tutorial 7 "7 is 2.645")
# do_test(Tutorial 25 "25 is 5")
# do_test(Tutorial -25 "-25 is [-nan|nan|0]")
# do_test(Tutorial 0.0001 "0.0001 is 0.01")
