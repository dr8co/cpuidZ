# cpuidz & cpuidzpp

`cpuidz` and `cpuidzpp` are two programs that detect various CPU features using the CPUID instruction.

[cpuidz](./main.c) is written in C, while [cpuidzpp](./main.cpp) is its C++ counterpart.

## Building

Follow the steps in the [main README](../README.md#building) to build the entire project,
including the library and the executables.

To skip building the C++ program, set the `BUILD_CPUIDZPP` CMake option to `OFF` when configuring the build:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc-14 -DCMAKE_CXX_COMPILER=g++-14 -DBUILD_CPUIDZPP=OFF -G Ninja
```
