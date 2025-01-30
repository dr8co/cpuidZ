# The C program
add_executable(cpuidz)
target_sources(cpuidz PRIVATE main.c)

option(BUILD_CPUIDZPP "Build the C++ program" ON)

# The C++ program
if (BUILD_CPUIDZPP)
    add_executable(cpuidzpp)
    target_sources(cpuidzpp PRIVATE main.cpp)
endif ()

# Debug compile options
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (MSVC)
        target_compile_options(cpuidz PRIVATE
                /W4
                /WX
        )
        if (BUILD_CPUIDZPP)
            target_compile_options(cpuidzpp PRIVATE
                    /W4
                    /WX
            )
        endif ()
    elseif (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
        target_compile_options(cpuidz PRIVATE
                -Wall
                -Wextra
                -Werror
        )
        if (BUILD_CPUIDZPP)
            target_compile_options(cpuidzpp PRIVATE
                    -Wall
                    -Wextra
                    -Werror
                    -Wpedantic
            )
        endif ()
    endif ()
endif ()

# Link the library to the programs
target_link_libraries(cpuidz PRIVATE cpuidx)

if (BUILD_CPUIDZPP)
    target_link_libraries(cpuidzpp PRIVATE cpuidx)
endif ()
