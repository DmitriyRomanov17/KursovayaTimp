/**
 * @file DataReader.cpp
 * @brief Implementation of the DataReader class that handles reading lines from a file.
 * 
 * This file contains the implementation of the `DataReader` class, which is responsible for 
 * reading lines from a specified file. It provides methods to read the next line and check 
 * for the end-of-file (EOF).
 * 
 * @author Romanov D.E.
 * @date 2024-12-19
 */

#include "DataReader.h"

/**
 * @class DataReader
 * @brief A class that reads lines from a file.
 * 
 * The `DataReader` class provides an interface to read lines from a file. It handles file 
 * opening, line reading, and checks for EOF. This class ensures that the file is properly 
 * opened before reading and properly closed after use.
 */
DataReader::DataReader(const std::string& filename) {
    file.open(filename);  /**< Opens the file specified by the filename. */
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file"); /**< Throws an exception if the file cannot be opened. */
    }
}

/**
 * @brief Reads the next line from the file.
 * 
 * This method reads the next line from the opened file and returns it as a string. If 
 * the end of the file is reached, it returns an empty string.
 * 
 * @return A string containing the next line from the file. If EOF is reached, returns an empty string.
 */
std::string DataReader::readNextLine() {
    std::string line; /**< Variable to store the line read from the file. */
    if (std::getline(file, line)) {
        return line; /**< Returns the line if successful. */
    }
    return {}; /**< Returns an empty string if EOF is reached. */
}

/**
 * @brief Checks if the end of the file is reached.
 * 
 * This method checks if the file stream has reached the end of the file.
 * 
 * @return `true` if EOF is reached, `false` otherwise.
 */
bool DataReader::eof() const {
    return file.eof(); /**< Returns true if EOF is reached, false otherwise. */
}

/**
 * @brief Destructor that closes the file if it is open.
 * 
 * The destructor ensures that the file is closed properly when the `DataReader` object
 * goes out of scope, preventing any resource leaks.
 */
DataReader::~DataReader() {
    if (file.is_open()) {
        file.close(); /**< Closes the file if it is open. */
    }
}

