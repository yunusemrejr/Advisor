#include <iostream>
#include <string>
#include <filesystem>

void analyze_folder(const std::string& path) {

  size_t file_count = 0;
  uintmax_t largest_file = 0;

  for (const auto& entry : std::filesystem::recursive_directory_iterator(path,std::filesystem::directory_options::skip_permission_denied)) {
      if(entry.is_regular_file()){

        ++file_count;
        auto size = entry.file_size();
        if(size > largest_file) largest_file = size;


      }

    }

    std::cout << "This action would delete " << file_count << " files and free up " << largest_file << 
    " bytes of space. The largest file is " << largest_file << " bytes." << std::endl;
}

int main(int argc, char* argv[]){
    if(argc < 2){
        std::cerr << "Usage: advisor <command> [args...]\n" << std::endl;
        return 1;
    }

     std::string cmd = argv[1];
    if (cmd == "reboot" || cmd == "shutdown") {
        std::cout << "You are requesting to " << cmd << " your computer.\n";
        std::cout << "Warning: All running applications will be closed, and unsaved work may be lost.\n";
    } else if (cmd == "rm" && argc >= 4 && std::string(argv[2]) == "-rf") {
        std::string folder = argv[3];
        std::cout << "You are requesting to recursively remove the contents of \"" << folder << "\".\n";
        analyze_folder(folder);
        std::cout << "Warning: This operation is irreversible. All contents in the specified folder would be permanently deleted.\n";
    } else {
        std::cout << "Command not recognized or not supported for analysis.\n";
    }
    return 0;
}