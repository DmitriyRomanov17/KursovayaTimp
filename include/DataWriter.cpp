/**
 * @file DataWriter.cpp
 * @brief Implementation of the DataWriter class that handles writing lines to a file.
 * 
 * This file contains the implementation of the `DataWriter` class, which is responsible for 
 * writing lines to a specified file. It provides methods for writing a line to the file 
 * and ensures that the file is properly opened before writing and properly closed after use.
 * 
 * @author Romanov D.E.
 * @date 2024-12-19
 */

#include "DataWriter.h"

/**
 * @class DataWriter
 * @brief A class that writes lines to a file.
 * 
 * The `DataWriter` class provides an interface to write lines to a file. It handles file 
 * opening, line writing, and ensures the file is properly closed after use.
 */
DataWriter::DataWriter(const std::string& filename) {
    file.open(filename);  /**< Opens the file specified by the filename. */
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing"); /**< Throws an exception if the file cannot be opened. */
    }
}

/**
 * @brief Writes a line to the file.
 * 
 * This method writes a line of text to the file, followed by a newline character. 
 * If the file is open, the line is written. If not, an exception was thrown earlier.
 * 
 * @param line The line of text to write to the file.
 */
void DataWriter::writeLine(const std::string& line) {
    file << line << std::endl;  /**< Writes the line and appends a newline character. */
}

/**
 * @brief Destructor that closes the file if it is open.
 * 
 * The destructor ensures that the file is closed properly when the `DataWriter` object
 * goes out of scope, preventing any resource leaks.
 */
DataWriter::~DataWriter() {
    if (file.is_open()) {
        file.close();  /**< Closes the file if it is open. */
    }
}

