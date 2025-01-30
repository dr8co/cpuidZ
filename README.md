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

## License

This project is licensed under the MIT License.

See the [LICENSE](./LICENSE) file for details.
