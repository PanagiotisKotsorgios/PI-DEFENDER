
#ifndef INCLUDES_H
#define INCLUDES_H

/**
 * @file includes.h
 * @brief Central header file for commonly used standard libraries.
 *
 * This header file consolidates the inclusion of frequently used C++ standard libraries,
 * such as iostream, fstream, sstream, string, and cstdlib. By including this file, other parts
 * of the project can easily access these libraries without redundant includes.
 *
 * @note The file also brings all names from the std namespace into the global namespace.
 *       Use this approach with caution in larger projects to avoid potential naming conflicts.
 *
 * @see http://www.cplusplus.com/reference/ for details on the standard library components.
 */

using namespace std; /**< Brings all identifiers from the std namespace into the global namespace. */

#include <iostream>   /**< Provides facilities for input and output operations (std::cout, std::cin, etc.). */
#include <fstream>    /**< Provides file stream classes for file I/O operations (std::ifstream, std::ofstream, etc.). */
#include <sstream>    /**< Provides string stream classes for in-memory string manipulation (std::istringstream, std::ostringstream, etc.). */
#include <string>     /**< Provides the std::string class and related string handling functionalities. */
#include <cstdlib>    /**< Provides general purpose functions, including dynamic memory management, random numbers, and system calls. */

#endif // INCLUDES_H
