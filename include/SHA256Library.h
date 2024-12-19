#ifndef DATA_WRITER_H
#define DATA_WRITER_H

#include <stdexcept>
#include <fstream>
#include <string>

/**
 * @brief Класс для записи данных в файл.
 */
class DataWriter {
private:
    /**
     * @brief Выходной файловый поток для записи данных.
     */
    std::ofstream file;

public:
    /**
     * @brief Конструктор класса DataWriter.
     * @param filename Имя файла, в который нужно записывать данные.
     * @throw std::runtime_error Если файл не удаётся открыть для записи.
     */
    explicit DataWriter(const std::string& filename);

    /**
     * @brief Записывает строку в файл.
     * @param line Строка, которая будет записана в файл.
     */
    void writeLine(const std::string& line);

    /**
     * @brief Деструктор класса DataWriter.
     * Закрывает файл, если он был открыт.
     */
    ~DataWriter();
};

#endif // DATA_WRITER_H

