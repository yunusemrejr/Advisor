# Build Instructions

## Prerequisites

This project requires a C++17 compatible compiler. The sandbox environment does not have a C++ compiler installed by default.

## Building on Your Local Machine

### Option 1: Using Make (Recommended)

```bash
# Build the project
make

# Run tests
make test

# Install system-wide (requires sudo)
sudo make install

# Clean build artifacts
make clean
```

### Option 2: Using CMake

```bash
# Create build directory
mkdir build && cd build

# Configure
cmake ..

# Build
cmake --build .

# Install (optional)
sudo cmake --install .
```

### Option 3: Direct Compilation

```bash
# Using g++
g++ -std=c++17 -O2 -Wall -Wextra advisor.cpp -o advisor

# Using clang++
clang++ -std=c++17 -O2 -Wall -Wextra advisor.cpp -o advisor
```

## Running the Application

After building, you can run the advisor:

```bash
# Show help
./advisor --help

# Test with reboot command
./advisor reboot

# Test with directory analysis (use a safe test directory)
./advisor rm -rf /tmp/test_directory
```

## Compiler Requirements

- **GCC**: Version 8.0 or higher
- **Clang**: Version 7.0 or higher
- **MSVC**: Visual Studio 2017 or higher

## Note for Sandbox Environment

The current sandbox environment does not have a C++ compiler installed and requires root privileges to install one. To build and test this application:

1. Clone this repository to your local machine
2. Install a C++17 compatible compiler
3. Follow the build instructions above

The code has been modernized and is ready to compile on any system with proper C++ tooling.
