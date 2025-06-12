
 #include "menus.h"
 #include <iostream>
 #include <cstdlib>           
 #include <thread>            
 #include <chrono>               
 
 using namespace std;
 

 void displayMenu() {
     cout << "\nSelect a tool to perform a scan:\n";
     cout << "1. Nmap (Basic Ping Scan)\n";
     cout << "2. Netdiscover (Network Discovery)\n";
     cout << "3. Nikto (Web Server Vulnerability Scanner)\n";
     cout << "4. Exit\n";
 }
 

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
 
