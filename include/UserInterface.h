/**
 * @file UserInterface.h
 * @brief Header file defining the UserInterface class, which handles command-line arguments and user input for a client program.
 * 
 * This file contains the declaration of the `UserInterface` class, which is responsible for parsing command-line 
 * arguments provided to the client program, validating the necessary parameters, and providing methods to display 
 * help and handle errors.
 * 
 * @author Romanov D.E.
 * @date 2024-12-19
 */

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <stdexcept>
#include <iostream>
#include <getopt.h>
#include <cstdlib>
#include <string>

/**
 * @class UserInterface
 * @brief Class responsible for managing user input, parsing command-line arguments, and validating input for the client application.
 * 
 * The `UserInterface` class handles the parsing of command-line arguments, ensuring that the user provides 
 * the necessary parameters for the client application to function. It validates the input, handles errors, 
 * and prints the help message if requested.
 */
class UserInterface {
public:
    /// Server address provided by the user
    std::string serverAddress;

    /// Server port, default is 33333 if not provided by the user
    int serverPort;

    /// Input file name provided by the user
    std::string inputFile;

    /// Output file name provided by the user
    std::string outputFile;

    /// Configuration file for LOGIN and PASSWORD (optional)
    std::string configFile;

    /**
     * @brief Constructor that parses the command-line arguments.
     * 
     * This constructor processes the command-line arguments passed to the program and stores the values 
     * for server address, port, input file, output file, and configuration file. It also validates the inputs 
     * and handles errors if necessary.
     * 
     * @param argc Number of arguments passed to the program
     * @param argv Array of argument strings passed to the program
     */
    UserInterface(int argc, char** argv);

    /**
     * @brief Prints the help message for the client program.
     * 
     * This static method displays the usage instructions for the client application, detailing the available 
     * command-line options and their descriptions.
     */
    static void printHelp();

    /**
     * @brief Handles errors by displaying an error message and terminating the program.
     * 
     * If an invalid or missing parameter is detected, this static method displays the provided error message 
     * and terminates the program.
     * 
     * @param message The error message to be displayed
     */
    static void handleError(const std::string& message);
};

#endif // USER_INTERFACE_H

