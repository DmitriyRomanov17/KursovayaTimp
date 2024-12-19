/**
 * @file DataWriter.h
 * @brief Header file for the DataWriter class that provides functionality for writing lines to a file.
 * 
 * This file defines the `DataWriter` class, which offers methods for writing lines to 
 * a specified file. The class ensures that the file is opened before writing and is properly 
 * closed when the object is destroyed.
 * 
 * @author Romanov D.E.
 * @date 2024-12-19
 */

#ifndef DATA_WRITER_H
#define DATA_WRITER_H

#include <stdexcept>
#include <fstream>
#include <string>

/**
 * @class DataWriter
 * @brief A class for writing lines to a file.
 * 
 * The `DataWriter` class provides an interface to write lines to a specified file. 
 * It handles file opening, line writing, and ensures proper file closure after use.
 */
class DataWriter {
private:
    std::ofstream file; /**< The output file stream used to write data to the file. */

public:
    /**
     * @brief Constructs a DataWriter object and opens the specified file for writing.
     * 
     * The constructor attempts to open the file specified by the `filename`. If the file 
     * cannot be opened, a `std::runtime_error` is thrown.
     * 
     * @param filename The name of the file to be opened for writing.
     * 
     * @throws std::runtime_error If the file cannot be opened for writing.
     */
    explicit DataWriter(const std::string& filename);

    /**
     * @brief Writes a line to the file.
     * 
     * This method writes a string to the file followed by a newline character. If the file 
     * is open, the line is written; otherwise, an exception was thrown earlier during 
     * construction.
     * 
     * @param line The line of text to write to the file.
     */
    void writeLine(const std::string& line);

    /**
     * @brief Destructor that ensures the file is closed when the DataWriter object is destroyed.
     * 
     * The destructor ensures that the file is properly closed if it is open, preventing 
     * any resource leaks when the object goes out of scope.
     */
    ~DataWriter();
};

#endif // DATA_WRITER_H

