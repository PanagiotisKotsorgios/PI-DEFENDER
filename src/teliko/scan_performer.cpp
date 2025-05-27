

#include "includes.h"
#include "executer.h"
#include <chrono> // For std::chrono
#include <thread> // For std::this_thread
#include "display_results.h"

#include <iostream>
#include <vector>
#include <string>
#include <regex>  // Add this line at the top of your file

#include <limits>  // For std::numeric_limits

// Function declaration
void executeCommandWithDebug(const std::string &command, const std::string &directory, const std::string &toolName, int scanType);



// Function to strip "/24" (or any subnet) from the IP address
std::string removeSubnet(const std::string& target) {
    size_t pos = target.find('/');
    if (pos != std::string::npos) {
        return target.substr(0, pos);  // Extract the part before the '/'
    }
    return target;  // Return as is if no '/' is found
}

void performNiktoScan(const std::string& target, const std::string& directory) {
    // Strip "/24" from target IP if present
    std::string cleanedTarget = removeSubnet(target);

    std::cout<<cleanedTarget;
    while(getchar()!='\n'){}
    // Execute Nikto scan with the cleaned target IP
    executeCommandWithDebug("nikto -h " + cleanedTarget + " -Tuning 1,2,3,4,5,6 -Display V -timeout 10", directory, "nikto_level1_output", 1);
}

void performNiktoScan2(const std::string& target, const std::string& directory) {
    // Strip "/24" from target IP if present
    std::string cleanedTarget = removeSubnet(target);

    std::cout<<cleanedTarget;
    while(getchar()!='\n'){}
    // Execute Nikto scan with the cleaned target IP
    executeCommandWithDebug("nikto -h " + cleanedTarget + " -Tuning 1,2,3,4,5,6,7,8 -Display VVV -timeout 10 -Plugins all -Format html -o " + directory + "/nikto_output.html -maxtime 3600s", directory, "nikto_level2_output", 2);

}


void performNiktoScan3(const std::string& target, const std::string& directory) {
    // Strip "/24" from target IP if present
    std::string cleanedTarget = removeSubnet(target);

    std::cout<<cleanedTarget;
    while(getchar()!='\n'){}
    // Execute Nikto scan with the cleaned target IP
   executeCommandWithDebug("nikto -h " + cleanedTarget + 
    " -Tuning 1,2,3,4,5,6,7,8"  // Keeps the existing tuning levels (vulnerabilities, misconfigurations, etc.)
    " -Display VVV"              // Verbosity set to maximum (VVV)
    " -timeout 10"               // Request timeout (10 seconds)
    " -Plugins all"              // Run all available plugins (best for thorough vulnerability scanning)
    " -Format html"              // Output in HTML format for better readability
    " -o " + directory + "/nikto_output.html"  // Output file location
    " -maxtime 3600s"            // Maximum scan time (3600 seconds = 1 hour)
    " -retries 5"                // Retry on failure (helps in case of transient issues with the target)
    " -UserAgent 'NiktoScanner/1.0'"  // Custom User-Agent string (helps to avoid detection as a scanner)
    " -nointeractive"            // Disables interactive prompts (useful for automation)
    " -ssl"                      // Enforces SSL mode for secure connections (helps in scanning HTTPS sites)
    " -ask+ no"                  // Avoid asking to submit updates, as it's not needed for this scan
    " -nossl"                    // This can be added if you want to avoid SSL
    " -mutate 2"                 // Guess file names for common file-related vulnerabilities
    " -maxtime 3600s"            // Scan timeout increased to 1 hour for deeper scanning
    " -followredirects"          // Follow redirects (important for sites with dynamic redirects)
    " -useproxy http://yourproxy:port" // Use a proxy if you're scanning behind a firewall
    " -Version"                  // Display version information of plugins and database
    " -no404"                    // Disables 404 response detection, speeding up the scan if you don't care about 404 pages"
    " -timeout 30"               // Increase timeout for more thorough investigation of each target (optional)
    , directory, "nikto_level3_output", 2);


}



#include <limits> // For std::numeric_limits

void performScanLevel1(const std::string &target) {
    std::cout << "[+] Performing Basic Scan (Level 1) on " << target << "...\n";
    
    // Define directory to save scan results
    std::string directory = "./scan_results";  // Directory to store results

    // Run nmap and save results with toolName "nmap_level1_output"
    executeCommandWithDebug("nmap -T5 --script=vuln -p- " + target, directory, "nmap_vuln_scan_level1_output", 1);

    // Run netdiscover in fast mode with parse results option to ensure it finishes
    executeCommandWithDebug("netdiscover -r " + target + " -f -P", directory, "netdiscover_level1_output", 1);

    // Ask if the user wants to use wpscan
    char wp_scan_condition = 'n';  // Default to 'n' for no
    std::cout << "Do you want to use wpscan? Y/n: ";
    
    try {
        std::cin >> wp_scan_condition;

        // Check if input failed (e.g., non-character input)
        if (std::cin.fail()) {
            throw std::runtime_error("Invalid input detected, expected a character.");
        }

        // Flush the input buffer to avoid issues with leftover characters
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (wp_scan_condition == 'y' || wp_scan_condition == 'Y') {
            std::cout << "Selected y / Y, selecting true to wp-scan usage.\n";
            executeCommandWithDebug("wpscan --url " + target + " --no-banner -f json", directory, "wpscan_level1_output", 1);  // Fixed wpscan command
        } 
        else if (wp_scan_condition == 'n' || wp_scan_condition == 'N') {
            std::cout << "Selected n / N, defaulting to no wp-scan usage.\n";
        } 
        else {
            std::cout << "Not valid user input provided: Defaulting to no wp-scan usage.\n";  // Fixed missing semicolon
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
        std::cout << "Defaulting to no wp-scan usage.\n";

        // Optional: Clear the error state and ignore remaining input
        std::cin.clear(); // Clear error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining input
    }

    // Perform the Nikto scan on the cleaned target IP
    performNiktoScan(target, directory);


    // Optionally, display the latest scan results for "nmap_level1_output"
    displayResults(directory, "nmap_level1_output");
    displayResults(directory, "netdiscover_level1_output");
    displayResults(directory, "nikto_level1_output");
    displayResults(directory, "wpscan_level1_output");
}





void showLoading() {
    std::string loading[] = {".", "..", "..."};
    for (int i = 0; i < 3; ++i) {
        std::cout << "\r[+] Scanning" << loading[i] << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Wait for a second
    }
    std::cout << std::endl;  // Move to the next line after the loading animation
}


void executeCommandWithDebug(const std::string &command, const std::string &directory, const std::string &toolName, int scanType) {
    // Print debug information
    std::cout << "[*] Executing command: " << command << std::endl;

    // Execute the command, passing all required parameters
    executeCommand(command, directory, toolName, scanType);

    // Print success message
    std::cout << "[+] Results saved in directory: " << directory << "/" << toolName << "_scanType" << scanType << ".txt" << std::endl;
}




void performScanLevel2(const std::string &target) {
    std::cout << "[+] Performing Intermediate Scan (Level 2) on " << target << "...\n";


    // Define directory to save scan results
    std::string directory = "./scan_results";  // Directory to store results

    // Run Nmap with advanced scanning and vulnerability scripts
    executeCommandWithDebug("nmap -T5 -A -sV --script=vulners,discovery,exploit,ssl-cert,ssl-enum-ciphers --top-ports 1000 " + target, directory, "nmap_level2_output", 2);

    // Run Masscan with optimized port scanning and banner grabbing
    executeCommandWithDebug("masscan -p1-65535 --rate=10000 --banners --ping-timeout 2000 " + target, directory, "masscan_level2_output", 2);

    // Run Nikto with enhanced web vulnerability scanning
      performNiktoScan2(target, directory);

    // Run Enum4linux for Linux enumeration with anonymous access
    executeCommandWithDebug("enum4linux -a -u anonymous -p '' " + target, directory, "enum4linux_level2_output", 2);

    // Run SMBMap with SMB enumeration (guest access and recursive search)
    //executeCommandWithDebug("smbmap -H " + target + " -u guest -p '' -R -v", directory, "smbmap_level2_output", 2);

    // Ask if the user wants to use wpscan
    char wp_scan_condition = 'n';  // Default to 'n' for no
    std::cout << "Do you want to use wpscan? Y/n: ";

    try {
        std::cin >> wp_scan_condition;

        // Check if input failed (e.g., non-character input)
        if (std::cin.fail()) {
            throw std::runtime_error("Invalid input detected, expected a character.");
        }

        // Flush the input buffer to avoid issues with leftover characters
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (wp_scan_condition == 'y' || wp_scan_condition == 'Y') {
            std::cout << "Selected y / Y, selecting true to wp-scan usage.\n";

            // Execute WPScan
            executeCommandWithDebug(
                "wpscan --url " + target + 
                " --no-banner " +  // Hides the banner information
                " --enumerate p,t,u " +  // Enumerate plugins (-p), themes (-t), and users (-u)
                " --vuln-detection " +  // Enable vulnerability detection
                " --plugins-detection mixed " +  // Use mixed detection for plugins (more aggressive)
                " --api-token YOUR_API_TOKEN " +  // Optional: Use WPScan API for up-to-date vulnerability checks
                " --f json",  // Output in JSON format
                directory, 
                "wpscan_level2_output", 
                1
            );
        } 
        else if (wp_scan_condition == 'n' || wp_scan_condition == 'N') {
            std::cout << "Selected n / N, defaulting to no wp-scan usage.\n";
        } 
        else {
            std::cout << "Not valid user input provided: Defaulting to no wp-scan usage.\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
        std::cout << "Defaulting to no wp-scan usage.\n";

        // Optional: Clear the error state and ignore remaining input
        std::cin.clear(); // Clear error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining input
    }

    // Execute openvas Scanner (if desired)
    std::cout << "Hopefully executing openvas Scanner: ";
    executeCommandWithDebug("gvm-cli --gmp-username your_username --gmp-password your_password --gmp-url https://your_gvm_host:9390 --xml='<create_task><name>Scan Task</name><target><host>" + 
        target + "</host></target></create_task>'", directory, "openvas_scan_output", 1);

    // Optionally, display the latest scan results
    displayResults(directory, "nmap_level2_output");
    displayResults(directory, "masscan_level2_output");
    displayResults(directory, "nikto_level2_output");
    displayResults(directory, "enum4linux_level2_output");
    //displayResults(directory, "smbmap_level2_output");

    std::cout << "[+] Intermediate Scan (Level 2) completed on " << target << ".\n";
}








void performScanLevel3(const std::string &target) {
    std::cout << "[+] Performing Advanced Scan (Level 3) on " << target << "...\n";

    // Define directory to save scan results
    std::string directory = "./scan_results";  // Directory to store results

    // Run Nmap with aggressive scan and vulnerability scripts
    executeCommandWithDebug("nmap -T5 -A -p- --script=vuln,vulners,exploit,ssl-enum-ciphers,discovery,safe,auth --script-timeout 90m --open --min-rate 1000 --max-retries 3 " + target, directory, "nmap_level3_output", 3);

    // Run Masscan with high rate and advanced configuration
    executeCommandWithDebug("masscan -p1-65535 --rate=20000 --open --banners --source-port 80 --ping-timeout 2000 --max-rate 50000 " + target, directory, "masscan_level3_output", 3);

    // Run Nikto with comprehensive tuning
    performNiktoScan3(target, directory);

    // Run Lynis for system auditing
    executeCommandWithDebug("lynis audit system --quiet --tests-from category --no-colors --log-file " + directory + "/lynis_level3_output.log", directory, "lynis_level3_output", 3);

    // Run SNMPWalk for SNMP enumeration
    executeCommandWithDebug("snmpwalk -v2c -c public -O e -r " + target, directory, "snmpwalk_level3_output", 3);

    // Run Hydra for brute-force SSH login
    executeCommandWithDebug("hydra -L users.txt -P passwords.txt -t 64 -f ssh://" + target, directory, "hydra_level3_output", 3);

    // Run Patator for FTP brute-force login
    //executeCommandWithDebug("patator ftp_login host=" + target + " user=admin password=admin -t 100", directory, "patator_level3_output", 3);

    // Run Metasploit for router penetration testing
    //executeCommandWithDebug("msfconsole -q -x \"use auxiliary/scanner/http/http_login; set RHOSTS " + target + "; set USERNAME admin; set PASSWORD admin; set THREADS 10; run\"", directory, "metasploit_level3_output", 3);

    // Ask if the user wants to use wpscan
    char wp_scan_condition = 'n';  // Default to 'n' for no
    std::cout << "Do you want to use wpscan? Y/n: ";

    try {
        std::cin >> wp_scan_condition;

        // Check if input failed (e.g., non-character input)
        if (std::cin.fail()) {
            throw std::runtime_error("Invalid input detected, expected a character.");
        }

        // Flush the input buffer to avoid issues with leftover characters
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (wp_scan_condition == 'y' || wp_scan_condition == 'Y') {
            std::cout << "Selected y / Y, selecting true to wp-scan usage.\n";

            // Execute WPScan
            executeCommandWithDebug(
                "wpscan --url " + target + 
                " --no-banner " +  // Hide banner information
                " --enumerate p,t,u,a " +  // Enumerate all plugins (-p), themes (-t), users (-u), and all additional available vulnerabilities (-a)
                " --vuln-detection mixed " +  // Enable mixed detection (aggressive detection of vulnerabilities)
                " --plugins-detection aggressive " +  // Aggressive plugin detection
                " --themes-detection aggressive " +  // Aggressive theme detection
                " --api-token YOUR_API_TOKEN " +  // Optional: WPScan API token for up-to-date vulnerabilities
                " --brute-forcedb /path/to/wordlist.txt " +  // Brute force DB (wordlist for user enumeration and passwords)
                " --passwords /path/to/wordlist.txt " +  // Wordlist for password brute force if login credentials are needed
                " --usernames admin,editor,guest,wpuser " +  // List of usernames to attempt for brute force
                " --f json --output " + directory + "/wpscan_level3_output.json",  // Output in JSON format to a specific file
                directory, 
                "wpscan_level3_output", 
                1
            );
        } 
        else if (wp_scan_condition == 'n' || wp_scan_condition == 'N') {
            std::cout << "Selected n / N, defaulting to no wp-scan usage.\n";
        } 
        else {
            std::cout << "Not valid user input provided: Defaulting to no wp-scan usage.\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
        std::cout << "Defaulting to no wp-scan usage.\n";

        // Optional: Clear the error state and ignore remaining input
        std::cin.clear(); // Clear error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining input
    }


    // Optionally, display the latest scan results
    displayResults(directory, "nmap_level3_output");
    displayResults(directory, "masscan_level3_output");
    displayResults(directory, "nikto_level3_output");
    displayResults(directory, "lynis_level3_output");
    displayResults(directory, "snmpwalk_level3_output");
    //isplayResults(directory, "hydra_level3_output");
    //displayResults(directory, "patator_level3_output");
    //displayResults(directory, "metasploit_level3_output");

    std::cout << "[+] Advanced Scan (Level 3) completed on " << target << ".\n";
}








void performCustomScan(const std::string &target) {
    // Define directory to save scan results
    std::string directory = "./scan_results";  // Directory to store results
    int scanOption = 0;

    try {
        // Display options and take scan option input
        std::cout << "[+] Custom Scan Options:\n";
        std::cout << "1. Scan specific port range (e.g., 80, 443)\n";
        std::cout << "2. Scan for specific vulnerabilities (e.g., SQL injection, XSS)\n";
        std::cout << "3. Run specific tool scan (e.g., nmap, nikto, hydra, openvas, metasploit, etc.)\n";
        std::cout << "Enter your custom scan option: ";
        std::cin >> scanOption;

        // Check for valid scanOption input
        if (std::cin.fail()) {
            throw std::invalid_argument("Invalid input detected for scan option.");
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer

        // Loop to allow multiple tools to be selected and execute their commands
        std::vector<std::string> selectedTools;
        bool addMoreTools = true;

        while (addMoreTools) {
            std::string tool;
            std::cout << "Enter tool to use (e.g., nmap, nikto, hydra, openvas, metasploit, wpscan, enum4linux, dirb, aircrack-ng, tcpdump) or type 'done' to finish: ";
            std::cin >> tool;

            if (tool == "done") {
                addMoreTools = false;
            } else {
                selectedTools.push_back(tool);
            }

            // Check for invalid tool name
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("Invalid tool name entered. Please enter a valid tool or 'done'.");
            }
        }

        // Execute custom scans for each selected tool
        for (const std::string &tool : selectedTools) {
            std::cout << "[+] Running " << tool << " on target " << target << "...\n";

            if (tool == "nmap") {
                std::string portRange;
                std::cout << "Enter port range for nmap (e.g., 80, 443) or press Enter to scan all ports: ";
                std::cin.ignore();  // To ignore any leftover newline character
                std::getline(std::cin, portRange);

                // Validate port range input (simple validation, should be extended)
                if (!portRange.empty() && !std::regex_match(portRange, std::regex("^[0-9,]+$"))) {
                    throw std::invalid_argument("Invalid port range format. Please provide comma-separated port numbers.");
                }

                std::string command = "nmap ";
                if (!portRange.empty()) {
                    command += "-p " + portRange + " ";
                }
                command += target;
                executeCommandWithDebug(command, directory, "nmap_custom_output", 4);
                displayResults(directory, "nmap_custom_output");
            }
            else if (tool == "nikto") {
                std::string vulnType;
                std::cout << "Enter vulnerability type for nikto (e.g., SQL, XSS): ";
                std::cin >> vulnType;

                // Validate input
                if (vulnType.empty() || vulnType.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != std::string::npos) {
                    throw std::invalid_argument("Invalid vulnerability type entered. Please enter a valid type.");
                }

                std::string command = "nikto -h " + target + " -Tuning 1 2 3 4 5 6 7 8 9 --vuln=" + vulnType;
                executeCommandWithDebug(command, directory, "nikto_custom_output", 4);
                displayResults(directory, "nikto_custom_output");
            }
            else if (tool == "hydra") {
                std::string usernameFile, passwordFile;
                std::cout << "Enter username file (e.g., users.txt): ";
                std::cin >> usernameFile;
                std::cout << "Enter password file (e.g., passwords.txt): ";
                std::cin >> passwordFile;

                // Check if file paths are valid (this could be enhanced further)
                if (usernameFile.empty() || passwordFile.empty()) {
                    throw std::invalid_argument("Username or password file path cannot be empty.");
                }

                std::string command = "hydra -L " + usernameFile + " -P " + passwordFile + " " + target + " ssh";
                executeCommandWithDebug(command, directory, "hydra_custom_output", 4);
                displayResults(directory, "hydra_custom_output");
            }
            else if (tool == "openvas") {
                std::string command = "openvas -h " + target;
                executeCommandWithDebug(command, directory, "openvas_custom_output", 4);
                displayResults(directory, "openvas_custom_output");
            }
            else if (tool == "wpscan") {
                std::cout << "Enter path to WordPress installation directory: ";
                std::string wpPath;
                std::cin >> wpPath;

                // Validate input
                if (wpPath.empty()) {
                    throw std::invalid_argument("WordPress installation path cannot be empty.");
                }

                std::string command = "wpscan --url " + target + " --path " + wpPath;
                executeCommandWithDebug(command, directory, "wpscan_custom_output", 4);
                displayResults(directory, "wpscan_custom_output");
            }
            else if (tool == "enum4linux") {
                std::string command = "enum4linux -a " + target;
                executeCommandWithDebug(command, directory, "enum4linux_custom_output", 4);
                displayResults(directory, "enum4linux_custom_output");
            }
            else if (tool == "metasploit") {
                std::string command = "msfconsole -q -x \"use exploit/windows/smb/ms17_010_eternalblue; set RHOSTS " + target + "; run\"";
                executeCommandWithDebug(command, directory, "metasploit_custom_output", 4);
                displayResults(directory, "metasploit_custom_output");
            }
            else if (tool == "dirb") {
                std::string command = "dirb http://" + target;
                executeCommandWithDebug(command, directory, "dirb_custom_output", 4);
                displayResults(directory, "dirb_custom_output");
            }
            else if (tool == "aircrack-ng") {
                std::cout << "Enter the path to the capture file (e.g., capture.cap): ";
                std::string captureFile;
                std::cin >> captureFile;

                if (captureFile.empty()) {
                    throw std::invalid_argument("Capture file path cannot be empty.");
                }

                std::string command = "aircrack-ng " + captureFile;
                executeCommandWithDebug(command, directory, "aircrackng_custom_output", 4);
                displayResults(directory, "aircrackng_custom_output");
            }
            else if (tool == "tcpdump") {
                std::string command = "tcpdump -i eth0 -w " + directory + "/tcpdump_output.pcap";
                executeCommandWithDebug(command, directory, "tcpdump_custom_output", 4);
                displayResults(directory, "tcpdump_custom_output");
            }
            else {
                std::cerr << "[Error] Invalid tool selected: " << tool << std::endl;
            }
        }
    }
    catch (const std::exception &e) {
        std::cerr << "[Error] Exception occurred: " << e.what() << std::endl;
        std::cout << "Please ensure your inputs are correct and try again.\n";
    }
}

