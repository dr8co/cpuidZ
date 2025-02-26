cmake_minimum_required(VERSION 3.30)

project(cpuidZ
        VERSION 2.0.0
        DESCRIPTION "A simple, lightweight x86 CPU features detector"
        LANGUAGES C ASM
)

# The C code is compatible with C99+, but compiling with C23 standard is recommended, if available
set(CMAKE_C_STANDARD 23)

# The program is built around a library
add_subdirectory(lib)

# Build the programs only if the project is standalone
if (PROJECT_IS_TOP_LEVEL)
    # The C++ program is written in C++23
    enable_language(CXX)
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    # The programs' sources
    add_subdirectory(src)

    # Conditional packaging (disabled by default)
    option(PACKAGE_PROJECT "Package the built project" OFF)

    if (PACKAGE_PROJECT)
        # Installation configuration
        include(GNUInstallDirs)

        # The library
        install(TARGETS cpuidx
                EXPORT cpuidx-targets
                LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT library
                ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT library
                RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT library
                PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT headers
        )

        # The CMake config files
        install(EXPORT cpuidx-targets
                FILE cpuidx-targets.cmake
                NAMESPACE cpuidx::
                DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cpuidx
                COMPONENT CMakeConfig
        )

        # The cpuidzpp executable program
        install(TARGETS cpuidzpp
                RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
                PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
                COMPONENT executables
        )

        include(CMakePackageConfigHelpers)

        # Create the version file
        write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/cpuidx-config-version.cmake"
                VERSION ${PROJECT_VERSION}
                COMPATIBILITY SameMajorVersion
        )

        # Create the config file
        configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/input_files/cpuidx-config.cmake.in"
                "${CMAKE_CURRENT_BINARY_DIR}/cpuidx-config.cmake"
                INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cpuidx"
        )

        # Install the config files
        install(FILES "${CMAKE_CURRENT_BINARY_DIR}/cpuidx-config.cmake"
                "${CMAKE_CURRENT_BINARY_DIR}/cpuidx-config-version.cmake"
                DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cpuidx"
                COMPONENT CMakeConfig
        )

        # Write the pkg-config file
        configure_file("${CMAKE_CURRENT_SOURCE_DIR}/input_files/libcpuidx.pc.in"
                "${CMAKE_CURRENT_BINARY_DIR}/libcpuidx.pc"
                @ONLY
        )

        # Install the pkg-config file
        install(FILES "${CMAKE_CURRENT_BINARY_DIR}/libcpuidx.pc"
                DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
                COMPONENT pkgconfig
        )

        # Packaging
        # Set the package properties
        set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
        set(CPACK_PACKAGE_VENDOR "Ian Duncan")
        set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
        set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})

        set(CPACK_PACKAGE_CONTACT "Ian Duncan <dr8co@duck.com>")
        set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/dr8co/cpuidZ")

        # Output directory
        set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_BINARY_DIR}/Packages")

        # Resource files
        set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
        set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)

        # Source package Generator variables
        set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
        set(CPACK_SOURCE_STRIP_FILES YES)
        set(CPACK_SOURCE_IGNORE_FILES
                /.git
                /.idea
                /.github
                /.vscode
                /.cache
                /build
                /cmake-build-*
                /CMakeFiles
                /CMakeScripts
                /CMakeModules
                /CMakeLists.txt.user
                /CMakeCache.txt
                /CTestTestfile.cmake
                /Makefile
                /Makefile.in
                /CPackConfig.cmake
                /CPackSourceConfig.cmake
                /CPackSourceConfig.cmake
                /CPack
        )

        # Set the package file name format
        set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
        set(CPACK_RPM_FILE_NAME RPM-DEFAULT)

        # Set the package generator
        if (WIN32)
            set(CPACK_GENERATOR "ZIP")
        elseif (APPLE)
            set(CPACK_GENERATOR "TGZ;DragNDrop")
        elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
            set(CPACK_GENERATOR "TGZ;DEB;RPM")
        else ()
            set(CPACK_GENERATOR "TGZ")
        endif ()

        set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.35), libstdc++6 (>= 14.2.0) libgcc-s1 (>= 14.2.0)")
        set(CPACK_RPM_PACKAGE_REQUIRES "glibc >= 2.35, libstdc++ >= 14.2.0, libgcc >= 14.2.0")

        # Use as many cores as available
        set(CPACK_THREADS "0")

        # Set the package architecture
        set(CPACK_PACKAGE_ARCHITECTURE "all")

        # Strip the binaries
        set(CPACK_STRIP_FILES YES)

        # Set the package license (RPM specific)
        set(CPACK_RPM_PACKAGE_LICENSE "MIT")

        # Set the section of the package
        set(CPACK_DEBIAN_PACKAGE_SECTION "libs")

        # Set the package checksum
        set(CPACK_PACKAGE_CHECKSUM "SHA256")

        include(CPack)

    endif ()
endif ()
