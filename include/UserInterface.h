#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <stdexcept>
#include <iostream>
#include <getopt.h>
#include <cstdlib>
#include <string>

/**
 * @brief Класс для обработки пользовательского интерфейса, включая работу с командной строкой.
 */
class UserInterface {
public:
    std::string serverAddress; /**< Адрес сервера. */
    int serverPort; /**< Порт сервера. */
    std::string inputFile; /**< Имя входного файла. */
    std::string outputFile; /**< Имя выходного файла. */
    std::string configFile; /**< Имя конфигурационного файла. */

    /**
     * @brief Конструктор, инициализирующий параметры командной строки.
     * @param argc Количество аргументов командной строки.
     * @param argv Массив аргументов командной строки.
     */
    UserInterface(int argc, char** argv);

    /**
     * @brief Выводит справку по использованию программы.
     */
    static void printHelp();

    /**
     * @brief Обрабатывает ошибку, выводя сообщение и завершает выполнение программы.
     * @param message Сообщение об ошибке.
     */
    static void handleError(const std::string& message);
};

#endif // USER_INTERFACE_H

