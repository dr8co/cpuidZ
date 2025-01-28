cmake_minimum_required(VERSION 3.25)
project(cpuidZ
        VERSION 1.0
        DESCRIPTION "A simple, lightweight x86 CPU features detector"
        LANGUAGES CXX C ASM)

# The C code is compatible with C99+, but compiling with C23 standard is recommended, if available
set(CMAKE_C_STANDARD 23)

# The C++ program, however, is written in C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib)

add_subdirectory(src)
