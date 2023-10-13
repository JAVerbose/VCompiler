cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

find_program(CCACHE_PROGRAM ccache)
if (CACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project (
    VCompiler
    LANGUAGES C
    VERSION 0.0.1
)

add_executable(
    VCompiler
    src/main.c
)