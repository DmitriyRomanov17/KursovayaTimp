#include "DataReader.h"

/**
 * @brief Конструктор класса DataReader.
 * @param filename Имя файла, который нужно открыть для чтения.
 * @throw std::runtime_error Если не удаётся открыть файл.
 */
DataReader::DataReader(const std::string& filename) {
    file.open(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }
}

/**
 * @brief Читает следующую строку из файла.
 * @return Строка из файла. Если файл закончился, возвращает пустую строку.
 */
std::string DataReader::readNextLine() {
    std::string line;
    if (std::getline(file, line)) {
        return line;
    }
    return {};
}

/**
 * @brief Проверяет, достигнут ли конец файла.
 * @return true, если конец файла достигнут, иначе false.
 */
bool DataReader::eof() const {
    return file.eof();
}

/**
 * @brief Деструктор класса DataReader.
 * Закрывает файл, если он открыт.
 */
DataReader::~DataReader() {
    if (file.is_open()) {
        file.close();
    }
}

