#ifndef DATA_READER_H
#define DATA_READER_H

#include <stdexcept>
#include <fstream>
#include <string>

/**
 * @brief Класс для чтения данных из текстового файла построчно.
 */
class DataReader {
private:
    /**
     * @brief Входной файловый поток для чтения данных.
     */
    std::ifstream file;

public:
    /**
     * @brief Конструктор класса DataReader.
     * @param filename Имя файла, который нужно открыть для чтения.
     * @throw std::runtime_error Если файл не удаётся открыть.
     */
    explicit DataReader(const std::string& filename);

    /**
     * @brief Читает следующую строку из файла.
     * @return Строка, прочитанная из файла. Если достигнут конец файла, возвращает пустую строку.
     */
    std::string readNextLine();

    /**
     * @brief Проверяет, достигнут ли конец файла.
     * @return true, если конец файла достигнут, иначе false.
     */
    bool eof() const;

    /**
     * @brief Деструктор класса DataReader.
     * Закрывает файл, если он был открыт.
     */
    ~DataReader();
};

#endif // DATA_READER_H

