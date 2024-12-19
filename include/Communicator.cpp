/**
 * @file Communicator.cpp
 * @brief Реализация класса для взаимодействия с сервером.
 * 
 * Класс Communicator предоставляет методы для подключения к серверу,
 * отправки и получения сообщений.
 */

#include "Communicator.h"

/**
 * @brief Конструктор класса Communicator.
 * 
 * @param serverAddress Адрес сервера.
 * @param serverPort Порт сервера.
 */
Communicator::Communicator(const std::string& serverAddress, int serverPort)
    : socketFd(-1), serverAddress(serverAddress), serverPort(serverPort) {}

/**
 * @brief Деструктор класса Communicator.
 * 
 * Закрывает сокет, если он был открыт.
 */
Communicator::~Communicator() {
    if (socketFd != -1) {
        close(socketFd);
    }
}

/**
 * @brief Подключается к серверу.
 * 
 * Создает сокет и устанавливает соединение с указанным сервером.
 * 
 * @throw std::runtime_error Если не удалось создать сокет или подключиться.
 */
void Communicator::connectToServer() {
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd == -1) {
        throw std::runtime_error("Failed to create socket");
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    if (inet_pton(AF_INET, serverAddress.c_str(), &serverAddr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid server address");
    }

    if (connect(socketFd, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == -1) {
        throw std::runtime_error("Failed to connect to server");
    }
}

/**
 * @brief Отправляет строковое сообщение на сервер.
 * 
 * @param message Сообщение для отправки.
 * 
 * @throw std::runtime_error Если отправка данных не удалась.
 */
void Communicator::sendMessage(const std::string& message) {
    sendMessage(message.c_str(), message.size());
}

/**
 * @brief Отправляет массив байтов на сервер.
 * 
 * @param data Указатель на массив данных.
 * @param size Размер массива данных.
 * 
 * @throw std::runtime_error Если отправка данных не удалась.
 */
void Communicator::sendMessage(const char* data, size_t size) {
    if (send(socketFd, data, size, 0) == -1) {
        throw std::runtime_error("Failed to send data");
    }
}

/**
 * @brief Получает строковое сообщение с сервера.
 * 
 * @param bufferSize Размер буфера для чтения.
 * @return Полученное сообщение.
 * 
 * @throw std::runtime_error Если получение данных не удалось.
 */
std::string Communicator::receiveMessage(size_t bufferSize) {
    std::string buffer(bufferSize, '\0');
    ssize_t bytesRead = recv(socketFd, buffer.data(), bufferSize, 0);
    if (bytesRead == -1) {
        throw std::runtime_error("Failed to receive data");
    }
    buffer.resize(bytesRead);
    return buffer;
}

/**
 * @brief Получает массив байтов от сервера.
 * 
 * @param buffer Указатель на буфер для записи данных.
 * @param size Ожидаемый размер данных.
 * 
 * @throw std::runtime_error Если размер полученных данных отличается от ожидаемого.
 */
void Communicator::receiveMessage(char* buffer, size_t size) {
    ssize_t bytesRead = recv(socketFd, buffer, size, 0);
    if (bytesRead != static_cast<ssize_t>(size)) {
        throw std::runtime_error("Failed to receive the expected amount of data");
    }
}

