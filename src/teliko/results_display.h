


 #ifndef RESULTS_DISPLAY_H
 #define RESULTS_DISPLAY_H
 
 /**
  * @brief Displays the results for all tools across all scan levels.
  *
  * This function is responsible for calling individual `displayResults` for each
  * tool and organizing their outputs by scan levels for comprehensive review.
  *
  * @details Tools are categorized by their scan levels (Level 1, Level 2, and Level 3),
  * and the function reads their respective result files to display information.
  *
  * @return void This function does not return a value.
  */
 void displayAllResults(int scan_level_code);
 
 #endif // RESULTS_DISPLAY_H
 
