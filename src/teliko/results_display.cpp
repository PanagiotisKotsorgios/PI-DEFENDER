


 #include "includes.h"
 #include "display_results.h"
 
 /**
  * @brief Displays the results for all tools across all scan levels.
  *
  * This function calls `displayResults` to read and print the results for predefined tool outputs.
  * It organizes the results based on tools and scan levels, allowing for easy review.
  *
  * Tools and Levels:
  * - Level 1: Basic scans with tools like Nmap and Netdiscover.
  * - Level 2: Intermediate scans with tools like Masscan, Nikto, and Enum4Linux.
  * - Level 3: Advanced scans with tools like Hydra, Patator, RouterSploit, and Lynis.
  *
  * @details The function relies on output files generated during the scan process, 
  * named using the format "<toolname>_level<level>_output.txt". Ensure that these files are present 
  * in the correct directory before invoking this function.
  *
  * @return void This function does not return a value.
  */
 void displayAllResults( int scan_level_code) {
 
 	std::cout << "\n\n-------------------------------";
 	std::cout << "\nDisplay Full scan Results Table\n";
 	std::cout << "-----------------------------------\n\n";
 	std::cout << "";	
 	
     std::cout<<scan_level_code;
 }
 
