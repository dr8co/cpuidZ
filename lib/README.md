# cpuidx Library

This simple library provides a way to detect various CPU features using the CPUID instruction.

It supports x86 and x86_64 architectures and provides detailed information about the CPU.

## Building

To build the entire project, including the library and the executables,
follow the steps in the [main README](../README.md#building).

To build a dynamic library instead of the default static library,
set the `BUILD_SHARED_LIBS` CMake option to `ON` when configuring the build:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc-14 -DCMAKE_CXX_COMPILER=g++-14 -DBUILD_SHARED_LIBS=ON -G Ninja
```
