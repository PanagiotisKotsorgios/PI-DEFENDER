

 #include "includes.h"           /**< @brief Custom header containing common project includes. */

 #include <fstream>              /**< @brief Provides file stream classes for file I/O operations. */
 #include <sstream>              /**< @brief Provides string stream classes for in-memory string manipulation. */
 #include <cstdlib>              /**< @brief Provides general purpose functions, including system calls. */
 #include <sys/stat.h>           /**< @brief Provides data returned by the stat() function. */
 
 #include <iostream>             /**< @brief Provides standard input-output stream objects. */
 #include <fstream>              /**< @brief Provides file stream classes for file I/O operations. */
 #include <sstream>              /**< @brief Provides string stream classes for in-memory string manipulation. */
 #include <cstdlib>              /**< @brief Provides general purpose functions, including system calls. */
 
 #include <ctime>                /**< @brief Provides functions and types for manipulating date and time. */
 #include <dirent.h>             /**< @brief Provides functions for directory traversal (opendir, readdir, closedir). */
 #include <cstring>              /**< @brief Provides functions for C-style string handling (e.g., strstr). */
 #include <cstdio>  // For popen, fclose
#include <memory>  // For unique_ptr
#include "executer.h"
#include <iomanip>
 /**
  * @brief Creates a directory if it does not exist.
  *
  * This function checks whether a directory specified by @p dirName exists. If it does not exist,
  * the function attempts to create the directory with permission mode 0777. Success or error messages
  * are printed to the standard output.
  *
  * @param dirName The name (or path) of the directory to check and potentially create.
  *
  * @return void This function does not return a value.
  *
  * @note The function uses the stat() function to determine if the directory exists and mkdir() to create it.
  *       It assumes a POSIX-compliant environment.
  */
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
 
 /**
  * @brief Executes a command and appends its output to a timestamped file in a given directory.
  *
  * This function ensures the specified directory exists, generates a unique output file name
  * based on the current timestamp, and then executes the provided command. The command output is
  * appended (using shell redirection) to the generated file. Finally, the function prints the location
  * of the saved output.
  *
  * @param command The shell command to execute.
  * @param directory The directory where the output file should be stored.
  * @param toolName A string representing the tool's name. This is used as part of the output file name.
  *
  * @return void This function does not return a value.
  *
  * @note The timestamp in the output file name is formatted as "YYYY-MM-DD_HH-MM-SS".
  *       The command output is redirected using the ">>" operator along with "2>&1" to capture both standard output and standard error.
  *       This function uses the system() call, which may be a security risk if used with untrusted input.
  */
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
