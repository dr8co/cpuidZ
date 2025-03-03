# The C program
add_executable(cpuidz)
target_sources(cpuidz PRIVATE main.c)

option(BUILD_CPUIDZPP "Build the C++ program" ON)

# The C++ program
if (BUILD_CPUIDZPP)
    add_executable(cpuidzpp)
    target_sources(cpuidzpp PRIVATE main.cpp)
endif ()

set(WARNING_FLAGS_GNU
        -Wall
        -Wextra
        -Werror
)

set(WARNING_FLAGS_MSVC
        /W4
        /WX
)

# Debug compile options
if (MSVC)
    target_compile_options(cpuidz PRIVATE
            $<$<CONFIG:Debug>:${WARNING_FLAGS_MSVC}>
    )
    if (BUILD_CPUIDZPP)
        target_compile_options(cpuidzpp PRIVATE
                $<$<CONFIG:Debug>:${WARNING_FLAGS_MSVC}>
        )
    endif ()
elseif (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    target_compile_options(cpuidz PRIVATE
            $<$<CONFIG:Debug>:${WARNING_FLAGS_GNU}>
    )
    if (BUILD_CPUIDZPP)
        target_compile_options(cpuidzpp PRIVATE
                $<$<CONFIG:Debug>:${WARNING_FLAGS_GNU}>
        )
    endif ()
endif ()

# Link the library to the programs
target_link_libraries(cpuidz PRIVATE cpuidx::cpuidx)

if (BUILD_CPUIDZPP)
    target_link_libraries(cpuidzpp PRIVATE cpuidx::cpuidx)
endif ()
