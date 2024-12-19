/**
 * @file main.cpp
 * @brief Main application logic for client-server communication and data processing.
 * 
 * This program reads configuration data, authenticates the client with the server,
 * processes input data, and sends the results back to the server. It handles reading
 * and writing files, as well as hashing passwords using SHA256.
 * 
 * @author Romanov.D.E.
 * @date 2024-12-19
 */

#include <stdexcept>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>

#include "include/SHA256Library.h"  ///< SHA256 hash utility
#include "include/UserInterface.h"  ///< User interface management
#include "include/Communicator.h"   ///< Communication with the server
#include "include/DataReader.h"     ///< Data reading utilities
#include "include/DataWriter.h"     ///< Data writing utilities

/** 
 * @brief Data type for vectors (double precision floating point).
 */
const std::string dataType = "double";

/** 
 * @brief Hashing algorithm used for authentication (SHA256).
 */
const std::string hashType = "SHA256";

/** 
 * @brief Side of the salt (server-side for this implementation).
 */
const std::string saltSide = "server";

/**
 * @brief Reads the login and password from a configuration file.
 * 
 * This function opens the specified configuration file, reads the login and password,
 * and throws an exception if the file cannot be opened or the credentials are invalid.
 * 
 * @param configFile The path to the configuration file.
 * @param login A reference to a string where the login will be stored.
 * @param password A reference to a string where the password will be stored.
 * @throws std::runtime_error If the file cannot be opened or credentials are invalid.
 */
void readLoginPassword(const std::string& configFile, std::string& login, std::string& password) {
    std::ifstream config(configFile);
    if (!config) {
        throw std::runtime_error("Failed to open config file: " + configFile);
    }

    std::getline(config, login);
    std::getline(config, password);

    if (login.empty() || password.empty()) {
        throw std::runtime_error("Invalid login or password in config file.");
    }
}

/**
 * @brief Authenticates the client with the server.
 * 
 * This function sends the username to the server, receives the salt, combines it with the
 * password, computes the SHA256 hash of the combination, and sends the hash back to the server.
 * If the server responds with anything other than "OK", authentication fails.
 * 
 * @param comm The Communicator object used for communication with the server.
 * @param password The password to be hashed and sent.
 * @throws std::runtime_error If authentication fails.
 */
void authenticateAsClient(Communicator& comm, const std::string& password) {
    std::string username = "user";
    comm.sendMessage(username);

    std::string salt(16, '\0');
    comm.receiveMessage(salt.data(), 16);

    std::string combined = salt + password;

    std::string calculatedHash = SHA256Library::hash(combined);
    
    for (char& c : calculatedHash) {
        c = std::toupper(static_cast<unsigned char>(c));
    }

    comm.sendMessage(calculatedHash);

    char response[2];
    comm.receiveMessage(response, sizeof(response));
    if (std::string(response, 2) != "OK") {
        throw std::runtime_error("Authentication failed");
    }
}

/**
 * @brief Reads a matrix of input data from a file.
 * 
 * This function opens the specified input file, reads its contents line by line, and
 * stores the data as a vector of vectors of doubles. It throws an exception if the file
 * cannot be opened or read.
 * 
 * @param inputFile The path to the input file.
 * @return A vector of vectors containing the input data.
 * @throws std::runtime_error If the file cannot be opened or read.
 */
std::vector<std::vector<double>> readInputFile(const std::string& inputFile) {
    std::ifstream file(inputFile);
    if (!file) {
        throw std::runtime_error("Failed to open input file: " + inputFile);
    }

    std::vector<std::vector<double>> vectors;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        vectors.emplace_back((std::istream_iterator<double>(iss)), std::istream_iterator<double>());
    }

    return vectors;
}

/**
 * @brief Writes the results of processing to an output file.
 * 
 * This function writes the processed results (a vector of doubles) to a specified binary
 * output file. The number of results is written first, followed by each result value.
 * 
 * @param outputFile The path to the output file.
 * @param results A vector containing the results to be written to the file.
 * @throws std::runtime_error If the file cannot be opened for writing.
 */
void writeResults(const std::string& outputFile, const std::vector<double>& results) {
    std::ofstream file(outputFile, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open output file: " + outputFile);
    }

    uint32_t numResults = results.size();
    file.write(reinterpret_cast<const char*>(&numResults), sizeof(numResults));

    for (const auto& result : results) {
        file.write(reinterpret_cast<const char*>(&result), sizeof(result));
    }
}

/**
 * @brief Main entry point for the application.
 * 
 * This function handles the overall workflow, including reading arguments, authenticating the
 * client, reading input data, processing the data, and writing results. It also handles error
 * reporting and provides help if required arguments are missing.
 * 
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 * @return An exit status code. Returns 0 on success, or 1 on failure.
 */
int main(int argc, char** argv) {
    try {
        if (argc < 2) {
            std::cerr << "Error: Missing required parameters.\n";
            UserInterface::printHelp();
            return 1;
        }

        UserInterface ui(argc, argv);
        Communicator comm(ui.serverAddress, ui.serverPort);

        comm.connectToServer();

        std::string login, password;
        readLoginPassword(ui.configFile, login, password);

        authenticateAsClient(comm, password);

        auto vectors = readInputFile(ui.inputFile);
        std::vector<double> results;

        uint32_t numVectors = vectors.size();
        comm.sendMessage(reinterpret_cast<const char*>(&numVectors), sizeof(numVectors));

        for (const auto& vec : vectors) {
            uint32_t vectorSize = vec.size();
            comm.sendMessage(reinterpret_cast<const char*>(&vectorSize), sizeof(vectorSize));
            comm.sendMessage(reinterpret_cast<const char*>(vec.data()), vec.size() * sizeof(double));

            double result;
            comm.receiveMessage(reinterpret_cast<char*>(&result), sizeof(result));
            results.push_back(result);
            std::cout << "Received result: " << result << std::endl;
        }

        writeResults(ui.outputFile, results);

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}

