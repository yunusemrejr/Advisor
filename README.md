# 🛡️ Command Advisor

**A modern, professional safety tool for analyzing dangerous system commands**

Command Advisor is a C++ utility that provides detailed analysis and warnings before executing potentially destructive system operations. It helps prevent accidental data loss and system disruption by giving you comprehensive insights into what a command will do.

---

## ✨ Features

- 🎨 **Beautiful Terminal UI** - Colored output with Unicode symbols for enhanced readability
- 📊 **Detailed Analysis** - Comprehensive statistics for file operations
- 🔍 **Smart File Scanning** - Recursive directory analysis with file type distribution
- 💾 **Human-Readable Sizes** - Automatic conversion to KB, MB, GB, TB
- ⚡ **Fast Performance** - Efficient C++17 implementation with modern features
- 🛡️ **Safety First** - Warns about dangerous operations without executing them
- 📝 **Comprehensive Help** - Built-in documentation and usage examples

---

## 🚀 Quick Start

### Prerequisites

- C++17 compatible compiler (GCC 8+, Clang 7+, MSVC 2017+)
- CMake 3.15 or higher (optional, for build system)

### Building with CMake (Recommended)

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

### Building with g++ (Direct)

```bash
g++ -std=c++17 -O2 -Wall -Wextra advisor.cpp -o advisor
```

---

## 📖 Usage

### Basic Syntax

```bash
advisor <command> [arguments...]
```

### Supported Commands

#### 1. System Reboot Analysis
```bash
advisor reboot
```
Analyzes the impact of rebooting your system, including warnings about:
- Running applications that will be terminated
- Unsaved work that may be lost
- Connected users that will be disconnected

#### 2. System Shutdown Analysis
```bash
advisor shutdown
```
Similar to reboot, provides comprehensive warnings about shutting down the system.

#### 3. Recursive Deletion Analysis
```bash
advisor rm -rf /path/to/directory
```
Performs deep analysis of the target directory, showing:
- Total number of files and directories
- Total size of data to be deleted
- Largest file information
- File type distribution (top 10)
- Human-readable size formatting

#### 4. Help
```bash
advisor help
# or
advisor --help
# or
advisor -h
```
Displays comprehensive help information with examples.

---

## 💡 Examples

### Example 1: Analyzing a directory deletion
```bash
$ advisor rm -rf /tmp/old_project

╔════════════════════════════════════════════════════════════════╗
║ DESTRUCTIVE OPERATION ADVISORY                                 ║
╚════════════════════════════════════════════════════════════════╝

Command: rm -rf /tmp/old_project

⚠️  WARNING: Recursive deletion requested!

🔍 Analyzing target directory...

📊 Analysis Results:
────────────────────────────────────────────────────────────────
  Total Files         : 1,247
  Total Directories   : 89
  Total Size          : 156.78 MB
  Largest File Size   : 45.23 MB
  Largest File Path   : /tmp/old_project/data/backup.tar.gz

  File Types Distribution:
    .js                 : 456 file(s)
    .json               : 234 file(s)
    .md                 : 123 file(s)
    .css                : 89 file(s)
    .html               : 67 file(s)
────────────────────────────────────────────────────────────────

⛔ DANGER: This operation is IRREVERSIBLE!
   All 1,247 files and 89 directories will be PERMANENTLY deleted.
   Total data loss: 156.78 MB

✓ Analysis complete. Review the information above carefully.
```

### Example 2: System reboot warning
```bash
$ advisor reboot

╔════════════════════════════════════════════════════════════════╗
║ SYSTEM COMMAND ADVISORY                                        ║
╚════════════════════════════════════════════════════════════════╝

Command: reboot

⚠️  WARNING: This will reboot your entire system!

  Impact              : All running applications will be terminated
  Data Loss Risk      : Any unsaved work will be lost
  Affected Users      : All logged-in users will be disconnected

⛔ This is a critical system operation. Ensure all work is saved!

✓ Analysis complete. Review the information above carefully.
```

---

## 🏗️ Architecture

### Code Structure

The application is organized into modular, well-documented functions:

- **Color Namespace** - ANSI color codes for terminal styling
- **AnalysisResult Struct** - Data structure for analysis results
- **Utility Functions** - Format bytes, get extensions, print helpers
- **Analysis Engine** - Recursive directory scanning and statistics
- **Command Handlers** - Specialized handlers for different command types
- **Main Entry Point** - Command routing and error handling

### Modern C++ Features Used

- ✅ C++17 filesystem library
- ✅ Structured bindings
- ✅ Lambda expressions
- ✅ Range-based for loops
- ✅ Smart error handling with exceptions
- ✅ STL containers (vector, map)
- ✅ String streams for formatting

---

## 🔒 Safety Features

### What This Tool Does
- ✅ Analyzes commands and provides detailed warnings
- ✅ Shows impact statistics and file information
- ✅ Helps prevent accidental data loss
- ✅ Educates users about command consequences

### What This Tool Does NOT Do
- ❌ Execute the actual commands
- ❌ Modify your system in any way
- ❌ Require root/admin privileges
- ❌ Store or transmit any data

---

## 🎨 Customization

### Disabling Colors

If your terminal doesn't support ANSI colors, you can modify the `Color` namespace in `advisor.cpp` to use empty strings:

```cpp
namespace Color {
    const std::string RESET = "";
    const std::string BOLD = "";
    // ... etc
}
```

### Adding New Commands

To add support for new dangerous commands, add a new handler in the `main()` function:

```cpp
else if (cmd == "your_command") {
    handle_your_command(/* args */);
}
```

---

## 🤝 Contributing

Contributions are welcome! Here are some ideas for improvements:

- [ ] Add support for more dangerous commands (dd, mkfs, etc.)
- [ ] Implement configuration file for custom warnings
- [ ] Add interactive confirmation prompts
- [ ] Create shell integration (alias wrapper)
- [ ] Add logging capabilities
- [ ] Support for Windows-specific commands

---

## 📋 Requirements

- **Operating System**: Linux, macOS, Unix-like systems
- **Compiler**: C++17 support required
  - GCC 8.0+
  - Clang 7.0+
  - MSVC 2017+
- **CMake**: 3.15+ (optional, for build system)

---

## 🐛 Troubleshooting

### Compilation Errors

**Error: `filesystem` not found**
- Ensure you're using C++17: `-std=c++17`
- For older GCC versions, link with: `-lstdc++fs`

**Error: Unicode symbols not displaying**
- Ensure your terminal supports UTF-8 encoding
- Set locale: `export LANG=en_US.UTF-8`

### Runtime Issues

**Permission denied when analyzing directories**
- The tool skips directories it can't access
- Run with appropriate permissions if needed (though not recommended)

---

## 📄 License

This project is open source and available for educational and personal use.

---

## 🙏 Acknowledgments

Built with modern C++ best practices and designed for safety-conscious system administrators and developers.

---

## 📞 Support

For bugs, feature requests, or questions:
- Open an issue on the project repository
- Review the help documentation: `advisor --help`

---

**Remember: This tool provides warnings and analysis only. Always double-check commands before execution!** 🛡️
