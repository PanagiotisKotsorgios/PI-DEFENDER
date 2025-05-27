

 #include "includes.h"           /**< @brief Custom header for common project includes. */
 #include <iostream>             /**< @brief Provides standard input-output stream objects. */
 #include <fstream>              /**< @brief Provides file stream classes for file I/O. */
 #include <sstream>              /**< @brief Provides string stream classes for in-memory string manipulation. */
 #include <cstdlib>              /**< @brief Provides general purpose functions, including dynamic memory management. */
 #include <sys/stat.h>           /**< @brief Provides structure and functions to obtain file status information. */
 #include <ctime>                /**< @brief Provides functions and types for manipulating date and time. */
 #include <dirent.h>             /**< @brief Provides functions for directory traversal (opendir, readdir, closedir). */
 #include <cstring>              /**< @brief Provides C string handling functions, such as strstr. */
 
 using namespace std;
 
 /**
  * @brief Reads and displays the latest scan results from a directory.
  *
  * This function searches the specified directory for files that match a naming pattern based on the provided tool name.
  * It identifies the latest file (determined by modification time) and outputs its content to the standard output.
  *
  * @param directory The directory path where result files are stored.
  * @param toolName The name of the tool whose result files are to be filtered and displayed. 
  *                 Files must contain this tool name as part of their name.
  *
  * @return void This function does not return any value.
  *
  * @exception std::runtime_error Although not explicitly throwing exceptions, errors are reported via stderr.
  *
  * @note The function relies on POSIX functions (opendir, readdir, closedir, stat) for directory operations
  *       and file status checking, hence it may not be portable to non-POSIX systems.
  *
  * @see opendir, readdir, closedir, stat, std::ifstream, std::ostringstream
  */
 void displayResults(const std::string &directory, const std::string &toolName) {
     // Build search pattern using the directory and tool name prefix.
     std::string searchPattern = directory + "/" + toolName + "_";
     std::string latestFile = "";  // Holds the path of the latest matching file.
     time_t latestTime = 0;        // Stores the modification time of the latest file.
 
     // Open the directory for reading.
     DIR *dir = opendir(directory.c_str());
     if (dir != nullptr) {
         struct dirent *entry;
         // Iterate over each entry in the directory.
         while ((entry = readdir(dir)) != nullptr) {
             // Check if the filename contains the tool name using strstr.
             if (strstr(entry->d_name, toolName.c_str())) {
                 std::string filePath = directory + "/" + entry->d_name;
                 struct stat fileStat;
                 stat(filePath.c_str(), &fileStat);
                 
                 // If the current file is newer, update the latest file information.
                 if (fileStat.st_mtime > latestTime) {
                     latestTime = fileStat.st_mtime;
                     latestFile = filePath;
                 }
             }
         }
         // Close the directory stream.
         closedir(dir);
 
         // If a matching file was found, open and display its contents.
         if (!latestFile.empty()) {
             std::ifstream file(latestFile);
             if (file.is_open()) {
                 std::ostringstream buffer;
                 buffer << file.rdbuf();
                 std::cout << "[Latest Results from " << toolName << "]\n";
                 std::cout << buffer.str() << "\n-----------------------------------\n";
                 file.close();
             } else {
                 std::cerr << "[Error] Could not open the latest file for reading results." << std::endl;
             }
         } else {
             std::cerr << "[Error] No results found for " << toolName << " in the directory." << std::endl;
         }
     } else {
         std::cerr << "[Error] Could not open directory " << directory << std::endl;
     }
 }
 
