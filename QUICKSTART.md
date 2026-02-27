# 🚀 Quick Start Guide

Get up and running with Command Advisor in under 2 minutes!

---

## Step 1: Build the Application

Choose your preferred build method:

### Option A: Using Make (Fastest)
```bash
make
```

### Option B: Using CMake (Most Flexible)
```bash
mkdir build && cd build
cmake ..
cmake --build .
cd ..
```

### Option C: Direct Compilation (Simplest)
```bash
g++ -std=c++17 -O2 -Wall advisor.cpp -o advisor
```

---

## Step 2: Run Your First Command

### See the Help
```bash
./advisor --help
```

### Test with Reboot Warning
```bash
./advisor reboot
```

**Expected Output:**
```
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

### Test with Directory Analysis
```bash
# Create a test directory
mkdir -p /tmp/test_advisor
echo "test" > /tmp/test_advisor/file1.txt
echo "test" > /tmp/test_advisor/file2.txt

# Analyze it
./advisor rm -rf /tmp/test_advisor

# Clean up
rm -rf /tmp/test_advisor
```

---

## Step 3: Install System-Wide (Optional)

```bash
sudo make install
```

Now you can run from anywhere:
```bash
advisor --help
```

---

## 🎯 Common Use Cases

### 1. Before Deleting a Directory
```bash
advisor rm -rf /path/to/directory
# Review the analysis
# Then decide whether to proceed
```

### 2. Before System Reboot
```bash
advisor reboot
# Check if you have unsaved work
# Then proceed with actual reboot if safe
```

### 3. Before System Shutdown
```bash
advisor shutdown
# Verify all users are notified
# Then proceed with actual shutdown
```

---

## 📚 Learn More

- **Full Documentation**: See [README.md](README.md)
- **Build Details**: See [BUILD.md](BUILD.md)
- **What's New**: See [CHANGELOG.md](CHANGELOG.md)
- **Improvements**: See [IMPROVEMENTS.md](IMPROVEMENTS.md)

---

## 🆘 Troubleshooting

### "Command not found" error
Make sure you're in the project directory or have installed system-wide.

### Compilation errors
Ensure you have a C++17 compatible compiler:
```bash
g++ --version  # Should be 8.0 or higher
```

### No colors in output
Your terminal may not support ANSI colors. The tool will still work, just without colors.

---

## ✅ You're Ready!

Command Advisor is now installed and ready to help you avoid dangerous command mistakes.

**Remember**: This tool only provides analysis. It does NOT execute commands.

---

*Happy safe computing! 🛡️*
