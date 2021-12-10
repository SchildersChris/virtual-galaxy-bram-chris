# CMake Template
A CMake project template

## Requirements
* CMake 3.12 or better; 3.14+ highly recommended.
* A C++17 compatible compiler
* The Boost libraries
* Doxygen

## Configure 
```bash
cmake -S . -B build
```
Add -GNinja if you have Ninja.

## Build
```bash
cmake --build build
```
## Docs
```bash
cmake --build build --target docs
```

## Test
```bash
cmake --build build --target test
```

# Credits
The base CMake starter has been taken from:  
https://gitlab.com/CLIUtils/modern-cmake/-/tree/master/examples/extended-project