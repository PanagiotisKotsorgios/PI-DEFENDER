

 #include "includes.h"        

 #include <fstream>            
 #include <sstream>         
 #include <cstdlib>              
 #include <sys/stat.h>       
 
 #include <iostream>             
 #include <fstream>            
 #include <sstream>             
 #include <cstdlib>           
 
 #include <ctime>                
 #include <dirent.h>          
 #include <cstring>             
 #include <cstdio>  // For popen, fclose
#include <memory>  // For unique_ptr
#include "executer.h"
#include <iomanip>
 void createDirectoryIfNeeded(const std::string &dirName) {
     struct stat info;
     if (stat(dirName.c_str(), &info) != 0) { // Directory doesn't exist
         if (mkdir(dirName.c_str(), 0777) == 0) {
             std::cout << "[Info] Directory " << dirName << " created successfully." << std::endl;
         } else {
             std::cerr << "[Error] Failed to create directory " << dirName << std::endl;
         }
     }
 }
 
void executeCommand(const std::string &command, const std::string &directory, const std::string &toolName, int scanType) {
    // Ensure the directory exists (assuming createDirectoryIfNeeded is implemented elsewhere)
    createDirectoryIfNeeded(directory);
    
    // Get the current time for timestamp generation
    std::time_t now = std::time(0);
    std::tm *ltm = std::localtime(&now);

    // Create a file name based on the scan type (e.g., scanType1.txt, scanType2.txt, etc.)
    std::string outputFile = directory + "/" + toolName + "_scanType" + std::to_string(scanType) + ".txt";

    // Open the file in append mode to add results to the end of the file
    std::ofstream outFile(outputFile, std::ios_base::app);

    if (outFile.is_open()) {
        // Write the timestamp of when the scan happens, with proper formatting
        outFile << "Scan Date and Time: " 
                << std::put_time(ltm, "%Y-%m-%d %H:%M:%S") << std::endl;

        // Open a pipe to the command and capture its output
        FILE* pipe = popen(command.c_str(), "r");
        if (!pipe) {
            std::cerr << "[Error] Failed to run command!" << std::endl;
            outFile.close();
            return;
        }

        // Read the command output line by line and append it to the file
        char buffer[128];
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            outFile << buffer;
        }

        // Close the pipe using pclose()
        pclose(pipe);  // This is the correct function to close a pipe

        // Add separator for clarity between different scans
        outFile << "-------------------------------------------" << std::endl;

        std::cout << "[Info] Results saved in " << outputFile << std::endl;
        outFile.close(); // Close the file after appending
    } else {
        std::cerr << "[Error] Could not open the file for appending!" << std::endl;
    }
}
