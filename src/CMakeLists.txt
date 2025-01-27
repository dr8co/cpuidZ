
add_executable(cpuidz main.c)

# Debug compile options
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (MSVC)
        target_compile_options(cpuidz PRIVATE
                /W4
                /WX
        )
    elseif (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
        target_compile_options(cpuidz PRIVATE
                -Wall
                -Wextra
                -Werror
#                -Wpedantic
        )
    endif ()
endif ()

target_link_libraries(cpuidz PRIVATE cpuidx)

