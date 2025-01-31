# The library
add_library(cpuidx)

if (MSVC)
    enable_language(ASM_NASM)
    set_source_files_properties(check_cpuid.asm PROPERTIES LANGUAGE ASM_MASM)
endif ()

target_sources(cpuidx PRIVATE
        cpuidx.c
        # The assembly file is platform-dependent
        $<IF:$<BOOL:${MSVC}>,check_cpuid_nasm.asm,check_cpuid.S>
)

# Options
option(BUILD_SHARED_LIBS "Build a shared library" OFF)

# MSVC Runtime Library and other settings
if (MSVC)
    if (BUILD_SHARED_LIBS)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    else ()
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif ()
endif ()

# Set the include directory for the library
target_include_directories(cpuidx PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Library properties
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
        )
    endif ()
endif ()
