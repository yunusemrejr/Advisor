/**
 * Command Advisor - A modern safety tool for dangerous system commands
 * 
 * This tool analyzes potentially dangerous commands and provides detailed
 * warnings and statistics before execution.
 * 
 * @author Command Advisor Team
 * @version 2.0.0
 * @date 2026
 */

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <map>
#include <cmath>

namespace fs = std::filesystem;

// ANSI Color Codes for terminal output
namespace Color {
    const std::string RESET = "\033[0m";
    const std::string BOLD = "\033[1m";
    const std::string RED = "\033[31m";
    const std::string YELLOW = "\033[33m";
    const std::string GREEN = "\033[32m";
    const std::string BLUE = "\033[34m";
    const std::string CYAN = "\033[36m";
    const std::string MAGENTA = "\033[35m";
}

/**
 * Structure to hold file analysis results
 */
struct AnalysisResult {
    size_t total_files = 0;
    size_t total_directories = 0;
    uintmax_t total_size = 0;
    uintmax_t largest_file_size = 0;
    std::string largest_file_path;
    std::map<std::string, size_t> file_types;
};

/**
 * Convert bytes to human-readable format (KB, MB, GB, TB)
 */
std::string format_bytes(uintmax_t bytes) {
    const char* units[] = {"B", "KB", "MB", "GB", "TB"};
    int unit_index = 0;
    double size = static_cast<double>(bytes);
    
    while (size >= 1024.0 && unit_index < 4) {
        size /= 1024.0;
        unit_index++;
    }
    
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << size << " " << units[unit_index];
    return oss.str();
}

/**
 * Get file extension from path
 */
std::string get_extension(const fs::path& path) {
    std::string ext = path.extension().string();
    return ext.empty() ? "[no extension]" : ext;
}

/**
 * Print a formatted header
 */
void print_header(const std::string& title) {
    std::cout << "\n" << Color::BOLD << Color::CYAN 
              << "╔════════════════════════════════════════════════════════════════╗\n"
              << "║ " << std::left << std::setw(62) << title << " ║\n"
              << "╚════════════════════════════════════════════════════════════════╝"
              << Color::RESET << "\n\n";
}

/**
 * Print a warning message
 */
void print_warning(const std::string& message) {
    std::cout << Color::BOLD << Color::YELLOW << "⚠️  WARNING: " 
              << Color::RESET << Color::YELLOW << message << Color::RESET << "\n";
}

/**
 * Print an error message
 */
void print_error(const std::string& message) {
    std::cerr << Color::BOLD << Color::RED << "❌ ERROR: " 
              << Color::RESET << Color::RED << message << Color::RESET << "\n";
}

/**
 * Print an info message
 */
void print_info(const std::string& label, const std::string& value) {
    std::cout << Color::BOLD << "  " << std::left << std::setw(20) << label << ": " 
              << Color::RESET << value << "\n";
}

/**
 * Analyze a folder and return detailed statistics
 */
AnalysisResult analyze_folder(const std::string& path) {
    AnalysisResult result;
    
    if (!fs::exists(path)) {
        throw std::runtime_error("Path does not exist: " + path);
    }
    
    if (!fs::is_directory(path)) {
        throw std::runtime_error("Path is not a directory: " + path);
    }
    
    try {
        for (const auto& entry : fs::recursive_directory_iterator(
            path, 
            fs::directory_options::skip_permission_denied)) {
            
            try {
                if (entry.is_regular_file()) {
                    result.total_files++;
                    auto size = entry.file_size();
                    result.total_size += size;
                    
                    // Track largest file
                    if (size > result.largest_file_size) {
                        result.largest_file_size = size;
                        result.largest_file_path = entry.path().string();
                    }
                    
                    // Track file types
                    std::string ext = get_extension(entry.path());
                    result.file_types[ext]++;
                    
                } else if (entry.is_directory()) {
                    result.total_directories++;
                }
            } catch (const fs::filesystem_error& e) {
                // Skip files we can't access
                continue;
            }
        }
    } catch (const fs::filesystem_error& e) {
        throw std::runtime_error("Error accessing directory: " + std::string(e.what()));
    }
    
    return result;
}

/**
 * Display detailed analysis results
 */
void display_analysis(const AnalysisResult& result) {
    std::cout << Color::BOLD << Color::BLUE << "\n📊 Analysis Results:\n" << Color::RESET;
    std::cout << std::string(64, '─') << "\n";
    
    print_info("Total Files", std::to_string(result.total_files));
    print_info("Total Directories", std::to_string(result.total_directories));
    print_info("Total Size", format_bytes(result.total_size));
    
    if (result.largest_file_size > 0) {
        print_info("Largest File Size", format_bytes(result.largest_file_size));
        print_info("Largest File Path", result.largest_file_path);
    }
    
    // Display top file types
    if (!result.file_types.empty()) {
        std::cout << "\n" << Color::BOLD << "  File Types Distribution:\n" << Color::RESET;
        
        // Sort by count
        std::vector<std::pair<std::string, size_t>> sorted_types(
            result.file_types.begin(), result.file_types.end());
        std::sort(sorted_types.begin(), sorted_types.end(),
            [](const auto& a, const auto& b) { return a.second > b.second; });
        
        // Show top 10
        size_t count = 0;
        for (const auto& [ext, num] : sorted_types) {
            if (count++ >= 10) break;
            std::cout << "    " << Color::CYAN << std::left << std::setw(20) << ext 
                      << Color::RESET << ": " << num << " file(s)\n";
        }
    }
    
    std::cout << std::string(64, '─') << "\n";
}

/**
 * Handle reboot/shutdown commands
 */
void handle_system_command(const std::string& cmd) {
    print_header("SYSTEM COMMAND ADVISORY");
    
    std::cout << Color::BOLD << "Command: " << Color::MAGENTA << cmd << Color::RESET << "\n\n";
    
    print_warning("This will " + cmd + " your entire system!");
    std::cout << "\n";
    print_info("Impact", "All running applications will be terminated");
    print_info("Data Loss Risk", "Any unsaved work will be lost");
    print_info("Affected Users", "All logged-in users will be disconnected");
    
    std::cout << "\n" << Color::BOLD << Color::RED 
              << "⛔ This is a critical system operation. Ensure all work is saved!\n" 
              << Color::RESET;
}

/**
 * Handle rm -rf commands
 */
void handle_remove_command(const std::string& path) {
    print_header("DESTRUCTIVE OPERATION ADVISORY");
    
    std::cout << Color::BOLD << "Command: " << Color::MAGENTA << "rm -rf " << path << Color::RESET << "\n\n";
    
    print_warning("Recursive deletion requested!");
    
    try {
        std::cout << "\n" << Color::YELLOW << "🔍 Analyzing target directory...\n" << Color::RESET;
        AnalysisResult result = analyze_folder(path);
        display_analysis(result);
        
        std::cout << "\n" << Color::BOLD << Color::RED 
                  << "⛔ DANGER: This operation is IRREVERSIBLE!\n"
                  << "   All " << result.total_files << " files and " 
                  << result.total_directories << " directories will be PERMANENTLY deleted.\n"
                  << "   Total data loss: " << format_bytes(result.total_size) << "\n"
                  << Color::RESET;
                  
    } catch (const std::exception& e) {
        print_error(e.what());
        std::cout << "\n" << Color::RED 
                  << "Unable to analyze directory, but deletion would still proceed if executed!\n" 
                  << Color::RESET;
    }
}

/**
 * Handle other dangerous commands
 */
void handle_dangerous_command(const std::string& cmd, const std::vector<std::string>& args) {
    print_header("POTENTIALLY DANGEROUS COMMAND");
    
    std::cout << Color::BOLD << "Command: " << Color::MAGENTA << cmd;
    for (const auto& arg : args) {
        std::cout << " " << arg;
    }
    std::cout << Color::RESET << "\n\n";
    
    print_warning("This command may have significant system impact!");
    std::cout << "\n" << Color::YELLOW 
              << "Please review the command carefully before execution.\n" 
              << Color::RESET;
}

/**
 * Display help information
 */
void show_help() {
    print_header("Command Advisor - Help");
    
    std::cout << Color::BOLD << "DESCRIPTION:\n" << Color::RESET;
    std::cout << "  A safety tool that analyzes potentially dangerous system commands\n";
    std::cout << "  and provides detailed warnings and impact analysis.\n\n";
    
    std::cout << Color::BOLD << "USAGE:\n" << Color::RESET;
    std::cout << "  advisor <command> [arguments...]\n\n";
    
    std::cout << Color::BOLD << "SUPPORTED COMMANDS:\n" << Color::RESET;
    std::cout << "  " << Color::CYAN << "reboot" << Color::RESET 
              << "              - Analyze system reboot impact\n";
    std::cout << "  " << Color::CYAN << "shutdown" << Color::RESET 
              << "            - Analyze system shutdown impact\n";
    std::cout << "  " << Color::CYAN << "rm -rf <path>" << Color::RESET 
              << "       - Analyze recursive deletion impact\n";
    std::cout << "  " << Color::CYAN << "help, --help, -h" << Color::RESET 
              << "  - Show this help message\n\n";
    
    std::cout << Color::BOLD << "EXAMPLES:\n" << Color::RESET;
    std::cout << "  advisor reboot\n";
    std::cout << "  advisor shutdown\n";
    std::cout << "  advisor rm -rf /tmp/old_data\n\n";
    
    std::cout << Color::BOLD << "NOTE:\n" << Color::RESET;
    std::cout << "  This tool only provides analysis and warnings.\n";
    std::cout << "  It does NOT execute the actual commands.\n\n";
}

/**
 * Main entry point
 */
int main(int argc, char* argv[]) {
    // Check for help flag
    if (argc < 2 || std::string(argv[1]) == "help" || 
        std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h") {
        show_help();
        return 0;
    }
    
    std::string cmd = argv[1];
    
    try {
        // Handle different command types
        if (cmd == "reboot" || cmd == "shutdown") {
            handle_system_command(cmd);
            
        } else if (cmd == "rm" && argc >= 4 && std::string(argv[2]) == "-rf") {
            std::string path = argv[3];
            handle_remove_command(path);
            
        } else if (cmd == "rm" && argc >= 3 && std::string(argv[2]) == "-rf") {
            print_error("Missing path argument for 'rm -rf' command");
            std::cout << "Usage: advisor rm -rf <path>\n";
            return 1;
            
        } else {
            // Generic dangerous command handler
            std::vector<std::string> args;
            for (int i = 2; i < argc; i++) {
                args.push_back(argv[i]);
            }
            handle_dangerous_command(cmd, args);
        }
        
    } catch (const std::exception& e) {
        print_error("An error occurred: " + std::string(e.what()));
        return 1;
    }
    
    std::cout << "\n" << Color::GREEN << "✓ Analysis complete. Review the information above carefully.\n" 
              << Color::RESET << "\n";
    
    return 0;
}
