#include <stdexcept>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>

#include "include/SHA256Library.h" // Собственная библиотека SHA256
#include "include/UserInterface.h"
#include "include/Communicator.h"
#include "include/DataReader.h"
#include "include/DataWriter.h"

const std::string dataType = "double";
const std::string hashType = "SHA256";
const std::string saltSide = "server";

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

