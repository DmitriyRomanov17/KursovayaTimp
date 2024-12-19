/**
 * @file DataReader.h
 * @brief Header file for the DataReader class that provides functionality for reading lines from a file.
 * 
 * This file defines the `DataReader` class, which offers methods for reading lines from 
 * a file. The class ensures that the file is opened before reading and is properly closed 
 * when the object goes out of scope.
 * 
 * @author Romanov D.E.
 * @date 2024-12-19
 */

#ifndef DATA_READER_H
#define DATA_READER_H

#include <stdexcept>
#include <fstream>
#include <string>

/**
 * @class DataReader
 * @brief A class for reading lines from a file.
 * 
 * The `DataReader` class allows reading lines from a specified file. It provides methods
 * to check for end-of-file (EOF), read the next line, and ensures proper resource management
 * by closing the file after use.
 */
class DataReader {
private:
    std::ifstream file; /**< The input file stream used to read data from the file. */
    
public:
    /**
     * @brief Constructs a DataReader object and opens the specified file.
     * 
     * The constructor attempts to open the file specified by the `filename`. If the file 
     * cannot be opened, a `std::runtime_error` is thrown.
     * 
     * @param filename The name of the file to be opened.
     * 
     * @throws std::runtime_error If the file cannot be opened.
     */
    explicit DataReader(const std::string& filename);

    /**
     * @brief Reads the next line from the file.
     * 
     * This method reads the next line from the file and returns it as a string. If the end 
     * of the file is reached, it returns an empty string.
     * 
     * @return A string containing the next line from the file. If EOF is reached, returns an empty string.
     */
    std::string readNextLine();

    /**
     * @brief Checks if the end of the file is reached.
     * 
     * This method checks if the file has reached its end and no more lines are available to read.
     * 
     * @return `true` if EOF is reached, `false` otherwise.
     */
    bool eof() const;

    /**
     * @brief Destructor that ensures the file is closed when the DataReader object is destroyed.
     * 
     * The destructor closes the file if it is open, ensuring proper resource management.
     */
    ~DataReader();
};

#endif // DATA_READER_H

