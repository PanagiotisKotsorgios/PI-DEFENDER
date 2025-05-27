
#ifndef SCAN_PERFORMER_H
#define SCAN_PERFORMER_H

/**
 * @file scan_performer.h
 * @brief Header file for network scanning functionalities.
 */

#include <string>

/**
 * @brief Performs a Level 1 (basic) network scan on the specified target.
 * 
 * This scan uses tools like Nmap and Netdiscover to gather basic information
 * about the target network or host.
 * 
 * @param target The target to scan (e.g., an IP address, domain, or network range).
 */
void performScanLevel1(const std::string &target);

// /**
//  * @brief Performs a Level 2 (intermediate) network scan on the specified target.
//  * 
//  * This scan includes vulnerability scans and port scanning using tools like
//  * Nmap with scripts, Masscan, and Nikto.
//  * 
//  * @param target The target to scan (e.g., an IP address, domain, or network range).
//  */
void performScanLevel2(const std::string &target);

// /**
//  * @brief Performs a Level 3 (advanced) network scan on the specified target.
//  * 
//  * This scan conducts comprehensive analysis, including vulnerability assessments,
//  * brute force testing, and advanced enumeration using multiple tools like
//  * Hydra, Nikto, and Lynis.
//  * 
//  * @param target The target to scan (e.g., an IP address, domain, or network range).
//  */
void performScanLevel3(const std::string &target);

// /**
//  * @brief Performs a custom network scan based on user input.
//  * 
//  * This scan allows users to define specific parameters, such as the tool to use,
//  * ports to scan, or specific vulnerabilities to test for.
//  * 
//  * @param target The target to scan (e.g., an IP address, domain, or network range).
//  */
 void performCustomScan(const std::string &target);
 
 

#endif // SCAN_PERFORMER_H
