# cpuidZ

cpuidZ is a simple tool to get CPUID information from the CPU.

It is written in C and uses the x86 `cpuid` instruction to retrieve the information.

## Features

- Detects various CPU features using the CPUID instruction
- Supports x86 and x86_64 architectures
- Provides detailed information about the CPU

## Requirements

- [CMake](https://cmake.org) 3.30 or higher
- C23 compatible C compiler
- C++23 compatible C++ compiler, such as [GCC](https://gcc.gnu.org) 14 or [Clang](https://clang.llvm.org) 18
- [Ninja](https://ninja-build.org) 1.12.1 or higher (optional, but recommended)

## Building

To build the project, follow these steps:

1. Clone the repository:
    ```sh
    git clone https://github.com/dr8co/cpuidZ.git
    cd cpuidZ
    ```

2. Create a build directory
    ```sh
    mkdir build
    ```

3. Run CMake to configure the project:
    ```sh
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc-14 -DCMAKE_CXX_COMPILER=g++-14 -G Ninja
    ```
   Replace `gcc-14` and `g++-14` with the path to your C and C++ compilers, respectively.

   If you don't have Ninja installed, omit the `-G` option to use the default generator for your platform.

4. Build the project:
    ```sh
    cmake --build build --config Release -j 4
    ```

## Usage

After building the project, you can run the executables to get CPUID information:

- For the C program:
    ```sh
    ./build/src/cpuidz
    ```

- For the C++ program:
    ```sh
    ./build/src/cpuidzpp
    ```

To use the library in your own project, use CMake's FetchContent module to include the library in your project:

```cmake
include(FetchContent)
FetchContent_Declare(
        cpuidz
        GIT_REPOSITORY https://github.com/dr8co/cpuidZ.git
        GIT_TAG v1.0.0
        EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(cpuidz)

# Link the library to your target
target_link_libraries(your_target PRIVATE cpuidzx::cpuidzx)
```

See [main.c](./src/main.c) and [main.cpp](./src/main.cpp) for examples on how to use the library.

For installation, visit the [Releases Page](https://github.com/dr8co/cpuidZ/releases)
to download the pre-built binaries.

## License

This project is licensed under the MIT License.

See the [LICENSE](./LICENSE) file for details.
