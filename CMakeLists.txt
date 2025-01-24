cmake_minimum_required(VERSION 3.25)
project(cpuid
        VERSION 1.0
        DESCRIPTION "A simple, lightweight x86 CPU features detector"
        LANGUAGES C ASM)

set(CMAKE_C_STANDARD 11)

add_executable(cpuid main.c $<IF:$<BOOL:${WIN32}>,check_cpuid.asm,check_cpuid.S>)

# Additional compile options for the Debug build
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (MSVC)
        target_compile_options(cpuid PRIVATE
                /W4
                /WX
        )
    elseif (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
        target_compile_options(cpuid PRIVATE
                -Wall
                -Wextra
                -Werror
                #                -Wpedantic
        )
    endif ()
endif ()
