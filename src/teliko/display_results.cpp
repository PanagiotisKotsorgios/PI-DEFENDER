

 #include "includes.h"          
 #include <iostream>             
 #include <fstream>           
 #include <sstream>           
 #include <cstdlib>            
 #include <sys/stat.h>         
 #include <ctime>                
 #include <dirent.h>             
 #include <cstring>              
 using namespace std;
 

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
 
