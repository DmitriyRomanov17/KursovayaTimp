#ifndef DATA_READER_H
#define DATA_READER_H

#include <stdexcept>
#include <fstream>
#include <string>

class DataReader {
private:
    std::ifstream file;
public:
    explicit DataReader(const std::string& filename);
    std::string readNextLine();
    bool eof() const;
    ~DataReader();
};

#endif // DATA_READER_H
