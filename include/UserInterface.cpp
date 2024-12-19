/**
 * @file UserInterface.cpp
 * @brief Implementation of the UserInterface class, handling command-line arguments and user input for a client program.
 * 
 * This file contains the implementation of the `UserInterface` class, which processes command-line 
 * arguments passed to the client program, validates the necessary parameters, and displays help messages 
 * or error messages as needed.
 * 
 * @author Romanov D.E.
 * @date 2024-12-19
 */

#include "UserInterface.h"

/**
 * @class UserInterface
 * @brief Class that manages user input, parses command-line arguments, and validates input for the client application.
 * 
 * The `UserInterface` class handles the parsing of command-line arguments, ensuring that the user provides 
 * the necessary parameters for the client application to function. It validates the input, handles errors, 
 * and prints the help message if requested.
 */
UserInterface::UserInterface(int argc, char** argv) : serverPort(33333), configFile(".config/client.config") {
    int opt;
    while ((opt = getopt(argc, argv, "a:p:i:o:c:h")) != -1) {
        switch (opt) {
            case 'a':
                serverAddress = optarg;
                break;
            case 'p':
                serverPort = std::stoi(optarg);
                break;
            case 'i':
                inputFile = optarg;
                break;
            case 'o':
                outputFile = optarg;
                break;
            case 'c':
                configFile = optarg;
                break;
            case 'h':
                printHelp();
                std::exit(0);
            default:
                handleError("Invalid option provided.");
                break;
        }
    }

    if (serverAddress.empty() || inputFile.empty() || outputFile.empty()) {
        handleError("Missing required parameters.");
    }
}

/**
 * @brief Prints the help message with usage instructions.
 * 
 * This method displays the usage instructions for the client application, detailing the available 
 * command-line options and their descriptions.
 */
void UserInterface::printHelp() {
    std::cout << "Usage: client -a <server_address> -p <server_port> -i <input_file> -o <output_file> -c <config_file>\n";
    std::cout << "Options:\n";
    std::cout << "  -a address     Server address (required)\n";
    std::cout << "  -p port        Server port (optional, default: 33333)\n";
    std::cout << "  -i input_file  Input file name (required)\n";
    std::cout << "  -o output_file Output file name (required)\n";
    std::cout << "  -c config_file Configuration file with LOGIN and PASSWORD (optional, default: .config/client.config)\n";
    std::cout << "  -h             Display help\n";
}

/**
 * @brief Handles errors by printing an error message and exiting the program.
 * 
 * If an invalid or missing parameter is detected, this method displays the provided error message 
 * and terminates the program.
 * 
 * @param message The error message to be displayed.
 */
void UserInterface::handleError(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
    std::exit(1);
}

