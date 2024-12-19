#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <unistd.h>
#include <string>

/**
 * @class Communicator
 * @brief Класс для общения клиента с сервером через TCP-соединение.
 *
 * Этот класс предоставляет методы для установки соединения, отправки и получения данных через TCP-сокет.
 */
class Communicator {
private:
    int socketFd; ///< Файловый дескриптор сокета.
    std::string serverAddress; ///< IP-адрес сервера.
    int serverPort; ///< Порт сервера.

public:
    /**
     * @brief Конструктор класса Communicator.
     * @param serverAddress Адрес сервера в формате строки.
     * @param serverPort Номер порта сервера.
     */
    Communicator(const std::string& serverAddress, int serverPort);

    /**
     * @brief Деструктор класса Communicator.
     * Закрывает сокет, если он открыт.
     */
    ~Communicator();

    /**
     * @brief Устанавливает соединение с сервером.
     * @throw std::runtime_error В случае ошибки при создании сокета или подключении к серверу.
     */
    void connectToServer();

    /**
     * @brief Отправляет сообщение серверу.
     * @param message Сообщение в виде строки.
     * @throw std::runtime_error В случае ошибки при отправке данных.
     */
    void sendMessage(const std::string& message);

    /**
     * @brief Отправляет массив байтов серверу.
     * @param data Указатель на массив данных.
     * @param size Размер массива данных.
     * @throw std::runtime_error В случае ошибки при отправке данных.
     */
    void sendMessage(const char* data, size_t size);

    /**
     * @brief Получает сообщение от сервера.
     * @param bufferSize Размер буфера для получения сообщения.
     * @return Сообщение от сервера в виде строки.
     * @throw std::runtime_error В случае ошибки при получении данных.
     */
    std::string receiveMessage(size_t bufferSize = 1024);

    /**
     * @brief Получает сообщение от сервера в указанный буфер.
     * @param buffer Указатель на буфер для записи данных.
     * @param size Ожидаемый размер сообщения.
     * @throw std::runtime_error Если получено меньше данных, чем ожидается, или при ошибке получения данных.
     */
    void receiveMessage(char* buffer, size_t size);
};

#endif // COMMUNICATOR_H

