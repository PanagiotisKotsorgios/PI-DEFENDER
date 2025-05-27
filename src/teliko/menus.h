
/**
 * @file menus.h
 * @brief Header file for the menu functionality of the scan tool application.
 *
 * This file declares the functions required to display a menu, select a tool, and execute a scan
 * based on the user's input. These functions facilitate the core interactive features of the application.
 */

 #ifndef MENUS_H
 #define MENUS_H
 
 #include <string> /**< @brief Provides support for the std::string class. */
 
 /**
  * @brief Displays the tool selection menu.
  *
  * This function prints a list of available scan tools and an exit option to the console.
  * The menu includes:
  *   - Nmap (Basic Ping Scan)
  *   - Netdiscover (Network Discovery)
  *   - Nikto (Web Server Vulnerability Scanner)
  *   - Exit
  *
  * @return void This function does not return a value.
  */
 void displayMenu();
 
 /**
  * @brief Prompts the user to select a tool from the menu.
  *
  * This function provides a user interface to select one of the available tools.
  * It validates the user's input to ensure it is a valid choice between 1 and 4.
  *
  * @return int The user's valid choice (1-4), where:
  *   - 1: Nmap
  *   - 2: Netdiscover
  *   - 3: Nikto
  *   - 4: Exit
  */
 int selectTool();
 
 /**
  * @brief Executes the command corresponding to the selected scan tool.
  *
  * This function constructs and executes the shell command associated with the user's tool selection
  * and specified target. The tools supported are:
  *   - Nmap: Performs a basic ping scan.
  *   - Netdiscover: Conducts network discovery with a timeout.
  *   - Nikto: Executes a web server vulnerability scan.
  *
  * @param toolChoice The tool selected by the user (1-3). Option 4 exits the application.
  * @param target The target IP address, range, or host for the scan.
  *
  * @return void This function does not return a value.
  *
  * @note This function uses the system() call to execute shell commands. Ensure input sanitization to prevent security risks.
  */
 void executeTool(int toolChoice, const std::string &target);
 
 #endif // MENUS_H
 
