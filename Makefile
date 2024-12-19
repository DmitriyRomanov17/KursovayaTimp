TARGET = client
TARGET_TEST = client_test

CXX = g++
CXXFLAGS = -Wall -std=c++17
CXXFLAGS_TEST = -std=c++17 -Wall -I/usr/include/UnitTest++
LDFLAGS_TEST = -L/usr/lib/x86_64-linux-gnu -lUnitTest++

SOURCES = main.cpp \
  include/Communicator.cpp \
  include/DataReader.cpp \
  include/DataWriter.cpp \
  include/UserInterface.cpp
SOURCES_TEST = test.cpp

all: build

build:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

test:
	$(CXX) $(CXXFLAGS_TEST) $(SOURCES_TEST) -o $(TARGET_TEST) $(LDFLAGS_TEST)
	./$(TARGET_TEST)
	rm -f $(TARGET_TEST)
