

#ifndef DISPLAY_RESULTS_H
#define DISPLAY_RESULTS_H

#include <string>

/**
 * @file display_results.h
 * @brief Declaration of the displayResults function.
 *
 * This header file declares the displayResults function, which is responsible for reading and 
 * displaying the latest scan result file for a given tool from a specified directory.
 *
 * @details The function searches the provided directory for files that match a naming pattern 
 * based on the tool name. It then determines the latest file based on the file modification time 
 * and outputs its contents to the standard output. This function relies on POSIX-compliant APIs 
 * (such as opendir, readdir, and stat) for directory traversal and file information.
 *
 * @author
 * @version 1.0
 * @date 2025-03-27
 *
 * @note This header should be included wherever the displayResults functionality is required.
 *
 * @see displayResults.cpp for the function implementation.
 */

/**
 * @brief Reads and displays the latest scan result file for the specified tool.
 *
 * This function scans the provided directory for files that contain the given tool name in their 
 * filenames, identifies the most recently modified file, and then prints its contents. If no file is found
 * or if there is an error in opening the directory or the file, an error message is printed to standard error.
 *
 * @param directory The directory path where the result files are stored.
 * @param toolName The tool name used to filter the result files (files should contain this as part of their name).
 *
 * @return void
 *
 * @exception std::runtime_error Although the function does not throw exceptions, errors are reported 
 * via standard error output.
 *
 * @note This function is intended for use on POSIX-compliant systems due to its reliance on specific 
 * system calls for directory handling.
 */


void displayResults(const std::string &directory, const std::string &toolName);

#endif // DISPLAY_RESULTS_H
