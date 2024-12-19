/**
 * @file Communicator.cpp
 * @brief Implementation of the Communicator class for handling communication with a server.
 * 
 * This file contains the implementation of the `Communicator` class, which provides functionality 
 * for creating a socket, connecting to a server, sending and receiving messages over the network.
 * It is used for establishing a TCP connection to a server and exchanging data between the client 
 * and the server.
 * 
 * @author Romanov D.E.
 * @date 2024-12-19
 */

#include "Communicator.h"

/**
 * @class Communicator
 * @brief A class for managing communication with a server.
 * 
 * The `Communicator` class provides methods for creating a socket, connecting to a server, 
 * sending messages, and receiving messages.
 */
Communicator::Communicator(const std::string& serverAddress, int serverPort)
    : socketFd(-1), serverAddress(serverAddress), serverPort(serverPort) {}

/**
 * @brief Destructor that closes the socket if it is open.
 * 
 * This destructor ensures that the socket is closed when the `Communicator` object is destroyed.
 * If the socket was successfully created (i.e., `socketFd` is not -1), it will be closed.
 */
Communicator::~Communicator() {
    if (socketFd != -1) {
        close(socketFd);
    }
}

/**
 * @brief Connects to the server using the provided address and port.
 * 
 * This method creates a socket, sets up the server address structure, and attempts to connect 
 * to the specified server using the `serverAddress` and `serverPort` passed during the 
 * construction of the `Communicator` object. If any of these steps fail, an exception will 
 * be thrown.
 * 
 * @throws std::runtime_error If the socket cannot be created, the server address is invalid, 
 *                             or the connection to the server fails.
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
 * @brief Sends a string message to the server.
 * 
 * This method sends the given message to the server over the established socket connection. 
 * It internally calls the `sendMessage` method that sends the message as raw data.
 * 
 * @param message The message to send to the server.
 * 
 * @throws std::runtime_error If the data cannot be sent to the server.
 */
void Communicator::sendMessage(const std::string& message) {
    sendMessage(message.c_str(), message.size());
}

/**
 * @brief Sends raw data to the server.
 * 
 * This method sends the provided data to the server. The data is sent using the `send` 
 * system call. The size of the data is specified by the `size` parameter.
 * 
 * @param data The raw data to send to the server.
 * @param size The size of the data to send.
 * 
 * @throws std::runtime_error If the data cannot be sent to the server.
 */
void Communicator::sendMessage(const char* data, size_t size) {
    if (send(socketFd, data, size, 0) == -1) {
        throw std::runtime_error("Failed to send data");
    }
}

/**
 * @brief Receives a message from the server with the specified buffer size.
 * 
 * This method receives a message from the server into a buffer of the specified size. The 
 * received data is returned as a string. If the number of bytes received is less than expected, 
 * the string is resized to match the actual number of bytes received.
 * 
 * @param bufferSize The size of the buffer to receive data into.
 * 
 * @return A string containing the received data.
 * 
 * @throws std::runtime_error If the data cannot be received or if the reception fails.
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
 * @brief Receives a fixed amount of data from the server into a buffer.
 * 
 * This method receives exactly the specified amount of data from the server and stores it in 
 * the provided buffer. If the number of bytes received does not match the expected size, 
 * an exception is thrown.
 * 
 * @param buffer The buffer to store the received data.
 * @param size The exact size of the data to receive.
 * 
 * @throws std::runtime_error If the expected amount of data is not received.
 */
void Communicator::receiveMessage(char* buffer, size_t size) {
    ssize_t bytesRead = recv(socketFd, buffer, size, 0);
    if (bytesRead != static_cast<ssize_t>(size)) {
        throw std::runtime_error("Failed to receive the expected amount of data");
    }
}

