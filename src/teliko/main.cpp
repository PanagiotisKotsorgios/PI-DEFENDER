

/**
 * @file includes_section.h
 * @brief Library Includes Section for the project.
 *
 * This file contains all the library inclusions required for the project.
 * Custom libraries are included first, followed by standard libraries.
 *
 * @details
 * - **Custom Libraries:**
 *   - @c includes.h: Contains most commonly used libraries in the project.
 *   - @c executer.h: Defines functions for the execution of the project.
 *   - @c display_results.h: Provides functions for displaying tool results.
 *   - @c scan_performer.h: Contains functions that handle tool usage (including system calls).
 *   - @c results_display.h: Manages the display of scan and log results.
 *
 * - **Standard Libraries:**
 *   - @c <stdexcept>: Required for exception handling in C++.
 *
 * @note Ensure that the custom headers are available in the include path.
 *
 * @see includes.h executer.h display_results.h scan_performer.h results_display.h
 */

// Custom Libraries Section
#include "includes.h"           /**< @brief Custom file for inclusion of mostly used libraries in the project. */
#include "executer.h"           /**< @brief Custom file for the execution functions of the project. */
#include "display_results.h"    /**< @brief Custom file for displaying the results of the tools. */
#include "scan_performer.h"     /**< @brief Custom file that contains functions for performing scans (includes system calls). */
#include "results_display.h"    /**< @brief Custom file for displaying the scan and log results. */

#include "fileSearcher.h"
// Standard Libraries Section
#include <stdexcept>            /**< @brief Standard header for exception handling in C++. */

// Using standard namespace
using namespace std;           /**< @brief Brings all the names from the std namespace into the global namespace. */


bool display_full_results = false;
char display_full_results_temp = 'n';
/**
 * @brief Prompts the user to select an operational mode.
 *
 * This function displays a menu of available modes and waits for user input. It validates
 * the input ensuring that the user selects either option 1 (Vulnerability Scan Mode) or 2 (N.I.D. & P. System Mode).
 *
 * @details If the user inputs an invalid option or a non-integer value, an exception is thrown and caught.
 * The error message is printed, and the function returns -1 to indicate an invalid selection.
 *
 * @exception std::invalid_argument Thrown if the user input is not 1 or 2.
 *
 * @return int Returns 1 or 2 based on the user's valid selection; returns -1 if invalid input is detected.
 *
 * @see PerformScanLevel(), PerformNidsMode()
 */
 
 using namespace std;
 
int selectMode(){;
    std::cout << "--------------\n" << endl;
    std::cout << "1. Vulnerability Scan Mode\n";
    std::cout << "2. NIDS Mode\n";
    std::cout << "3. SEARCHER Mode\n\n";
   
    try {
        int user_mode_option = 0;
        cout << "#> ";
        cin >> user_mode_option;

        // Validate input: check for failure or invalid option (only 1 or 2 are allowed)
        if (cin.fail() || (user_mode_option != 1 && user_mode_option != 2)) {
            throw invalid_argument("Invalid option. Please enter 1 or 2.");
        }

        return user_mode_option;
    }
    catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
        // Return -1 to signal that the input was invalid.
        return -1;
    }
}

/**
 * @brief Displays the vulnerability scanner menu and processes scan level selection.
 *
 * This function presents a detailed menu with options for various scan levels including basic, intermediate,
 * advanced, and custom scans. It prompts the user to select a scan level and provide a target (IP range or host).
 *
 * @details Depending on the chosen scan level, the function calls the respective scan function. 
 * Currently, only a basic scan operation (performScanLevel1) is implemented. Other scan levels are placeholders.
 * After performing the scan, it calls displayAllResults() to show the results.
 *
 * @note The functions performScanLevel1, performScanLevel2, performScanLevel3, performCustomScan, and displayAllResults
 * are assumed to be defined elsewhere.
 *
 * @return void This function does not return a value.
 *
 * @see selectMode()
 */
void PerformScanLevel() {
    
    int scanLevel;
    std::string target;
    int customScanOption;

    // Display vulnerability scanner menu header and options.
    std::cout << "====================================\n";
    std::cout << "     Vulnerability Scanner Menu    \n";
    std::cout << "====================================\n";
    std::cout << "Choose Scan Level:\n" << endl;
    cout << "--------------------\n";
    std::cout << "1. Basic Scan\n";
    cout << "--------------------\n";
    std::cout << "2. Intermediate Scan\n";
    cout << "--------------------\n";
    std::cout << "3. Advanced Scan\n";
    cout << "--------------------\n";
    std::cout << "4. Custom Scan\n";  // Option for a custom scan.
    cout << "--------------------\n" << endl;
    
    // Prompt the user for the desired scan level.
    std::cout << "Enter your choice: ";
    std::cin >> scanLevel;

 
    // Prompt for target specification (e.g., IP range or host).
    std::cout << "Enter the target (IP range or host): ";
    std::cin >> target;
    
    std::cout<<"Do you want to display full results in the end of the scanning proccess? Y/n : ";
    std::cin >> display_full_results_temp;
    
    if(display_full_results_temp == 'Y' || display_full_results_temp == 'y'){
        display_full_results = true;
    }
    else if(display_full_results_temp == 'N' || display_full_results_temp == 'n'){
    	display_full_results = false;
    }
    else{
     cerr << "Invalid input: Keeping false as default value ;)";
    }

    // Switch based on the selected scan level.
    switch (scanLevel) {
        case 1:
            // Call basic scan function.
            performScanLevel1(target);
            break;
        case 2:
            // Placeholder for intermediate scan logic.
             performScanLevel2(target);
            
            break;
        case 3:
            // Placeholder for advanced scan logic.
            performScanLevel3(target);
            break;
        case 4:
            // Custom scan option: additional custom parameter is requested.
            std::cout << "Enter custom scan option (e.g., specific port range, vulnerability type, etc.): ";
            std::cin >> customScanOption;
            // Placeholder for custom scan logic.
            performCustomScan(target);
            break;
        default:
            std::cerr << "[Error] Invalid scan level. Please choose 1, 2, 3, or 4." << std::endl;
            return;
    }

     if(display_full_results == true){
     	// After scan completion, display the results.
    	std::cout << "[+] Scan completed. Displaying results:\n";
    	displayAllResults(scanLevel);
     }
     else if(display_full_results == false){
     	std::cout << "[+] Scan Completed.";
     }
    
}

/**
 * @brief Displays the N.I.D. & P. System menu and executes the selected functionality.
 *
 * This function shows a menu for NIDS functionality with four levels: basic, intermediate, advanced, and custom.
 * It validates the user input and then calls the corresponding operation function based on the selection.
 *
 * @details The function uses exception handling to manage invalid inputs. If an invalid option is entered,
 * an exception is thrown and an error message is displayed.
 *
 * @exception std::invalid_argument Thrown if the user input is non-integer or outside the valid range (1-4).
 *
 * @return void This function does not return a value.
 *
 * @see selectMode()
 */
void PerformNidsMode() {
    
}






void activateFileSearcher() {
    Search_In_File();
}



/**
 * @brief Main function: Entry point for the program.
 *
 * This function first calls selectMode() to determine which mode the user wants to execute.
 * It then routes the program flow to either the Vulnerability Scanner mode or the N.I.D. & P. System mode.
 *
 * @details If the mode selected is invalid (indicated by -1), the program prompts the user to try again.
 * The function ensures a clean program exit after processing the user input.
 *
 * @return int Returns 0 upon successful program termination.
 *
 * @see selectMode(), PerformScanLevel(), PerformNidsMode()
 */
int main(int argc, char* argv[]) {
    // Check if enough arguments are passed
    if (argc != 2) {
        cout << "Usage: ./program <mode>" << endl;
        cout << "Valid modes: 1 (Scan Level), 2 (NIDS Mode), 3 (SEARCHER MODE)" << endl;
        return 1; // Exit with error code
    }

    try {
        // Obtain the operational mode from the command-line argument
        int mode = stoi(argv[1]);  // Convert the argument to an integer

        // Check if the mode is valid
        if (mode == 1) {
            cout << "You selected mode: " << mode << endl;
            PerformScanLevel();
        }
        else if (mode == 2) {
            cout << "You selected mode: " << mode << endl;
            PerformNidsMode();
        }
        else if (mode == 3){
            activateFileSearcher();
        }
        else {
            cout << "Invalid mode selected. Please choose 1 or 2." << endl;
            return 1; // Exit with error code for invalid mode
        }
    } catch (const invalid_argument& e) {
        cout << "Invalid input. The mode should be an integer. Error: " << e.what() << endl;
        return 1; // Exit with error code for invalid argument
    } catch (const out_of_range& e) {
        cout << "Input is out of range. Please provide a valid mode. Error: " << e.what() << endl;
        return 1; // Exit with error code for out-of-range argument
    }

    return 0; // Exit with success
}




