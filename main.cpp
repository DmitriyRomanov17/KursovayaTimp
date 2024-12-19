/**
 * @file main.cpp
 * @brief Главный файл программы для взаимодействия с сервером и обработки данных.
 * 
 * Этот файл реализует клиентскую часть взаимодействия, включая:
 * - Чтение конфигурации.
 * - Аутентификацию.
 * - Отправку данных на сервер.
 * - Получение результатов.
 */

#include <stdexcept>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>

#include "include/SHA256Library.h" // Собственная библиотека SHA256
#include "include/UserInterface.h"
#include "include/Communicator.h"
#include "include/DataReader.h"
#include "include/DataWriter.h"

/** @brief Тип данных для обработки. */
const std::string dataType = "double";
/** @brief Тип хеширования для аутентификации. */
const std::string hashType = "SHA256";
/** @brief Определяет сторону, где используется "соль". */
const std::string saltSide = "server";

/**
 * @brief Считывает логин и пароль из конфигурационного файла.
 * @param configFile Путь к конфигурационному файлу.
 * @param login Переменная для хранения логина.
 * @param password Переменная для хранения пароля.
 * @throw std::runtime_error Если файл недоступен или содержит некорректные данные.
 */
void readLoginPassword(const std::string& configFile, std::string& login, std::string& password);

/**
 * @brief Аутентифицирует клиента на сервере.
 * @param comm Объект класса Communicator для взаимодействия с сервером.
 * @param password Пароль для аутентификации.
 * @throw std::runtime_error Если аутентификация не удалась.
 */
void authenticateAsClient(Communicator& comm, const std::string& password);

/**
 * @brief Считывает входной файл с векторами данных.
 * @param inputFile Путь к входному файлу.
 * @return Векторы данных, считанные из файла.
 * @throw std::runtime_error Если файл недоступен.
 */
std::vector<std::vector<double>> readInputFile(const std::string& inputFile);

/**
 * @brief Записывает результаты в файл.
 * @param outputFile Путь к выходному файлу.
 * @param results Вектор результатов для записи.
 * @throw std::runtime_error Если файл недоступен.
 */
void writeResults(const std::string& outputFile, const std::vector<double>& results);

/**
 * @brief Точка входа в программу.
 * 
 * Реализует:
 * - Обработку аргументов командной строки.
 * - Инициализацию объектов.
 * - Аутентификацию и взаимодействие с сервером.
 * - Чтение данных из файлов и запись результатов.
 * 
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return Код завершения программы (0 - успех, 1 - ошибка).
 */
int main(int argc, char** argv);

