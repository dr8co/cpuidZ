cmake_minimum_required(VERSION 3.25)
project(cpuid
        VERSION 1.0
        DESCRIPTION "A simple, lightweight x86 CPU features detector"
        LANGUAGES C ASM)

set(CMAKE_C_STANDARD 23)

add_subdirectory(lib)

add_subdirectory(src)
