TARGET = client

CXX = g++
CXXFLAGS = -Wall -std=c++17

SOURCES = main.cpp \
		 include/Communicator.cpp \
		 include/DataReader.cpp \
		 include/DataWriter.cpp \
		 include/UserInterface.cpp

LIBRARIES = library/libcryptopp.a

all: build

build:
	$(CXX) $(CXXFLAGS) $(SOURCES) $(LIBRARIES) -o $(TARGET)

