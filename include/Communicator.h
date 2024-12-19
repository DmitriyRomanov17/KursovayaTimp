/**
 * @file Communicator.h
 * @brief Header file for the Communicator class, responsible for handling communication with a server.
 * 
 * This file defines the `Communicator` class, which provides functionality for establishing a 
 * network connection to a server, sending and receiving messages over a socket.
 * 
 * The `Communicator` class uses a socket to establish a TCP connection with the server and 
 * provides methods to send and receive messages between the client and the server.
 * 
 * @author Romanov D.E.
 * @date 2024-12-19
 */

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
 * @brief A class for managing communication with a server over a TCP socket.
 * 
 * The `Communicator` class provides methods for creating a socket, connecting to a server,
 * sending and receiving messages to and from the server. It abstracts the low-level socket 
 * operations and provides an interface for communication over the network.
 * 
 * This class is used for establishing a connection to a remote server and exchanging data
 * over that connection.
 */
class Communicator {
private:
    int socketFd; /**< Socket file descriptor used for communication. */
    std::string serverAddress; /**< Server address in string format. */
    int serverPort; /**< Server port number. */
    
public:
    /**
     * @brief Constructs a Communicator object with the specified server address and port.
     * 
     * The constructor initializes the `Communicator` object with the server address and port
     * that will be used for establishing a connection to the server.
     * 
     * @param serverAddress The address of the server to connect to.
     * @param serverPort The port number of the server to connect to.
     */
    Communicator(const std::string& serverAddress, int serverPort);

    /**
     * @brief Destructor that closes the socket if it is open.
     * 
     * The destructor ensures that the socket is closed when the `Communicator` object goes out 
     * of scope, preventing resource leaks.
     */
    ~Communicator();

    /**
     * @brief Establishes a connection to the server.
     * 
     * This method creates a socket, prepares the server address structure, and attempts to 
     * connect to the specified server. If any error occurs during these operations, 
     * a `std::runtime_error` is thrown.
     * 
     * @throws std::runtime_error If the socket cannot be created, the server address is invalid, 
     *                             or the connection to the server fails.
     */
    void connectToServer();

    /**
     * @brief Sends a message to the server as a string.
     * 
     * This method sends a message (in the form of a string) to the server over the established 
     * connection. It calls the lower-level `sendMessage` method to send the data.
     * 
     * @param message The message to send to the server.
     * 
     * @throws std::runtime_error If the data cannot be sent to the server.
     */
    void sendMessage(const std::string& message);

    /**
     * @brief Sends raw data to the server.
     * 
     * This method sends the provided data to the server. The size of the data is specified 
     * by the `size` parameter.
     * 
     * @param data The raw data to send to the server.
     * @param size The size of the data to send.
     * 
     * @throws std::runtime_error If the data cannot be sent to the server.
     */
    void sendMessage(const char* data, size_t size);

    /**
     * @brief Receives a message from the server with the specified buffer size.
     * 
     * This method receives a message from the server and stores it in a buffer. The buffer size 
     * can be specified using the `bufferSize` parameter (default is 1024). If the number of bytes 
     * received is less than expected, the returned string will be resized to match the actual 
     * number of bytes received.
     * 
     * @param bufferSize The size of the buffer to receive the data into. Default is 1024.
     * 
     * @return A string containing the received data.
     * 
     * @throws std::runtime_error If the data cannot be received or if the reception fails.
     */
    std::string receiveMessage(size_t bufferSize = 1024);

    /**
     * @brief Receives a fixed amount of data from the server into a provided buffer.
     * 
     * This method receives exactly the specified amount of data from the server and stores it 
     * in the provided `buffer`. If the number of bytes received does not match the specified 
     * size, an exception is thrown.
     * 
     * @param buffer The buffer to store the received data.
     * @param size The exact number of bytes to receive.
     * 
     * @throws std::runtime_error If the expected amount of data is not received.
     */
    void receiveMessage(char* buffer, size_t size);
};

#endif // COMMUNICATOR_H

