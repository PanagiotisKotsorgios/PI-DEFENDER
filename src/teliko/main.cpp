
// Custom Libraries Section
#include "includes.h"          
#include "executer.h"           
#include "display_results.h"    
#include "scan_performer.h"
#include "results_display.h"    

#include "fileSearcher.h"
// Standard Libraries Section
#include <stdexcept>           

// Using standard namespace
using namespace std;           


bool display_full_results = false;
char display_full_results_temp = 'n';

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


void PerformNidsMode() {
    
}






void activateFileSearcher() {
    Search_In_File();
}



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




