
#ifndef EXECUTER_H
#define EXECUTER_H

#include <string>

/**
 * @file executer.h
 * @brief Declaration of the executeCommand function.
 *
 * This header file declares the executeCommand function, which is responsible for executing
 * a shell command and redirecting its output (both standard output and standard error) to a
 * uniquely named, timestamped file within a specified directory.
 *
 * @details The function ensures that the target directory exists, constructs a unique file name
 * based on the current timestamp and the provided tool name, and then executes the command by appending
 * its output to this file.
 *
 * @note This function is designed to work on POSIX-compliant systems due to its reliance on system calls
 * and directory management functions. Caution should be exercised when using the system() call due to
 * potential security risks if untrusted input is provided.
 *
 * @see executer.cpp for the implementation details.
 */

/**
 * @brief Executes a shell command and redirects its output to a timestamped file.
 *
 * This function performs the following operations:
 *  - Ensures that the specified directory exists (creating it if necessary).
 *  - Generates a unique output file name based on the current timestamp and the given tool name.
 *  - Executes the provided shell command, redirecting both standard output and standard error to the output file.
 *  - Informs the user about the location of the saved output file.
 *
 * @param command The shell command to execute.
 * @param directory The directory in which the output file should be stored.
 * @param toolName A string representing the tool's name; used as a prefix in the output file name.
 *
 * @return void This function does not return a value.
 */




void executeCommand(const std::string &command, const std::string &directory, const std::string &toolName, int scanType);



#endif // EXECUTER_H
