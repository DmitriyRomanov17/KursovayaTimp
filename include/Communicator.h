#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <unistd.h>
#include <string>

class Communicator {
private:
    int socketFd;
    std::string serverAddress;
    int serverPort;
public:
    Communicator(const std::string& serverAddress, int serverPort);
    ~Communicator();

    void connectToServer();

    void sendMessage(const std::string& message);
    void sendMessage(const char* data, size_t size);

    std::string receiveMessage(size_t bufferSize = 1024);
    void receiveMessage(char* buffer, size_t size);
};

#endif // COMMUNICATOR_H