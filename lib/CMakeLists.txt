
add_library(cpuidx)
target_sources(cpuidx PRIVATE
        cpuidx.c
        $<IF:$<BOOL:${WIN32}>,check_cpuid.asm,check_cpuid.S>
)

# Set the include directory for the library
target_include_directories(cpuidx PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_target_properties(cpuidx PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER cpuidx.h
)

# Additional compile options for the Debug build
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (MSVC)
        target_compile_options(cpuidx PRIVATE
                /W4
                /WX
        )
    elseif (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
        target_compile_options(cpuidx PRIVATE
                -Wall
                -Wextra
                -Werror
#                -Wpedantic
        )
    endif ()
endif ()
