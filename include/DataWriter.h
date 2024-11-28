#ifndef DATA_WRITER_H
#define DATA_WRITER_H

#include <stdexcept>
#include <fstream>
#include <string>

class DataWriter {
private:
    std::ofstream file;
public:
    explicit DataWriter(const std::string& filename);
    void writeLine(const std::string& line);
    ~DataWriter();
};

#endif // DATA_WRITER_H
