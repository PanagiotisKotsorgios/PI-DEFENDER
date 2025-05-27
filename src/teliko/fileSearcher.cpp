#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

bool startsWith(const std::string& line, const std::string& prefix) {
    return line.compare(0, prefix.size(), prefix) == 0;
}

int Search_In_File() {
    std::string directory, pattern, stopPrefix;

    std::cout << "Enter the directory path: ";
    std::getline(std::cin, directory);

    std::cout << "Enter the pattern to search for: ";
    std::getline(std::cin, pattern);

    std::cout << "Enter the stop prefix (e.g., 'Scan Date and Time:'): ";
    std::getline(std::cin, stopPrefix);

    fs::path dirPath = fs::absolute(directory);
    std::cout << "Looking in: " << dirPath << std::endl;

    if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
        std::cerr << "Invalid directory path." << std::endl;
        return 1;
    }

    bool foundAny = false;

    for (const auto& entry : fs::directory_iterator(dirPath)) {
        if (entry.path().extension() == ".txt") {
            std::ifstream file(entry.path());
            if (!file) {
                std::cerr << "Error opening file: " << entry.path() << std::endl;
                continue;
            }

            std::string line;
            int lineNumber = 1;
            bool foundPattern = false;
            bool foundInFile = false;

            std::cout.flush();

            while (std::getline(file, line)) {
                if (!foundPattern && line.find(pattern) != std::string::npos) {
                    if (!foundInFile) {
                        std::cout << "\nIn file: " << entry.path().filename() << std::endl;
                        foundInFile = true;
                        foundAny = true;
                    }
                    std::cout << "  Line " << lineNumber << ": " << line << std::endl;
                    foundPattern = true;
                }
                else if (foundPattern) {
                    if (startsWith(line, stopPrefix)) {
                        break; // stop printing when another scan block starts
                    }
                    std::cout << "  Line " << lineNumber << ": " << line << std::endl;
                }

                lineNumber++;
            }

            file.close();
        }
    }

    if (!foundAny) {
        std::cout << "No matches found in any .txt files in the directory." << std::endl;
    }

    return 0;
}

