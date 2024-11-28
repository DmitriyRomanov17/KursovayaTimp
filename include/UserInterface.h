#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <stdexcept>
#include <iostream>
#include <getopt.h>
#include <cstdlib>
#include <string>

class UserInterface {
public:
    std::string serverAddress;
    int serverPort;
    std::string inputFile;
    std::string outputFile;
    std::string configFile;

    UserInterface(int argc, char** argv);
    static void printHelp();
    static void handleError(const std::string& message);
};

#endif // USER_INTERFACE_H
