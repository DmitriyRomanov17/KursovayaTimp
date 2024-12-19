#include "DataWriter.h"

/**
 * @brief Конструктор класса DataWriter.
 * @param filename Имя файла, который нужно открыть для записи.
 * @throw std::runtime_error Если не удаётся открыть файл.
 */
DataWriter::DataWriter(const std::string& filename) {
    file.open(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing");
    }
}

/**
 * @brief Записывает строку в файл.
 * @param line Строка, которая будет записана в файл.
 */
void DataWriter::writeLine(const std::string& line) {
    file << line << std::endl;
}

/**
 * @brief Деструктор класса DataWriter.
 * Закрывает файл, если он был открыт.
 */
DataWriter::~DataWriter() {
    if (file.is_open()) {
        file.close();
    }
}

