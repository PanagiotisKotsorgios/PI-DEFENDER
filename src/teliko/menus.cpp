
 #include "menus.h"              /**< @brief Header file with function prototypes for the menu system. */
 #include <iostream>             /**< @brief Provides standard input and output stream objects. */
 #include <cstdlib>              /**< @brief Provides system() for executing shell commands. */
 #include <thread>               /**< @brief Provides std::this_thread::sleep_for for thread sleeping. */
 #include <chrono>               /**< @brief Provides time duration types, e.g., std::chrono::seconds. */
 
 using namespace std;
 
 /**
  * @brief Displays the scan tool selection menu.
  *
  * This function prints the available scan tools and an exit option to the console.
  * The menu includes:
  *   - Nmap (Basic Ping Scan)
  *   - Netdiscover (Network Discovery)
  *   - Nikto (Web Server Vulnerability Scanner)
  *   - Exit
  *
  * @return void This function does not return any value.
  */
 void displayMenu() {
     cout << "\nSelect a tool to perform a scan:\n";
     cout << "1. Nmap (Basic Ping Scan)\n";
     cout << "2. Netdiscover (Network Discovery)\n";
     cout << "3. Nikto (Web Server Vulnerability Scanner)\n";
     cout << "4. Exit\n";
 }
 
 /**
  * @brief Prompts the user to select a tool from the menu.
  *
  * This function repeatedly prompts the user to enter a choice between 1 and 4.
  * If an invalid choice is entered, the user is prompted again.
  *
  * @return int The user's valid choice (1-4).
  */
 int selectTool() {
     int choice;
     while (true) {
         cout << "Enter your choice (1-4): ";
         cin >> choice;
 
         if (choice >= 1 && choice <= 4) {
             return choice;
         } else {
             cout << "Invalid choice. Please try again.\n";
         }
     }
 }
 
 /**
  * @brief Executes the command corresponding to the selected scan tool.
  *
  * This function builds and executes a shell command based on the user's selected tool and target.
  * Depending on the toolChoice:
  *   - For Nmap, a basic ping scan is executed.
  *   - For Netdiscover, a network discovery command is executed with a 30-second timeout.
  *   - For Nikto, a web server vulnerability scan is executed.
  *   - For the Exit option, the function prints an exit message and returns immediately.
  *
  * After executing the command, the function pauses for 5 seconds before returning to allow the user to review the output.
  *
  * @param toolChoice The tool selection (1 for Nmap, 2 for Netdiscover, 3 for Nikto, 4 for Exit).
  * @param target The target (IP address, range, or host) on which the scan is to be performed.
  *
  * @return void This function does not return a value.
  *
  * @note The system() function is used to execute shell commands, which may have security implications if used with untrusted input.
  */
 void executeTool(int toolChoice, const std::string &target) {
     string command;
 
     switch (toolChoice) {
         case 1:
             cout << "[+] Executing Nmap (Basic Ping Scan) on " << target << "...\n";
             command = "nmap -sP " + target;
             system(command.c_str());
             break;
 
         case 2:
             cout << "[+] Executing Netdiscover (Network Discovery) on " << target << "...\n";
             command = "timeout 30s sh -c 'netdiscover -r " + target + " </dev/null'";
             system(command.c_str());
             break;
 
         case 3:
             cout << "[+] Executing Nikto (Web Server Vulnerability Scanner) on " << target << "...\n";
             command = "nikto -h " + target;
             system(command.c_str());
             break;
 
         case 4:
             cout << "Exiting...\n";
             return;
 
         default:
             cout << "Invalid tool choice.\n";
             break;
     }
 
     cout << "[*] Scan completed. Waiting for 5 seconds before returning to the menu...\n";
     this_thread::sleep_for(chrono::seconds(5));
 }
 
