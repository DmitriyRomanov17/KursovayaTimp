# Название исполняемого файла
TARGET = client

# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Флаги для связывания с библиотекой OpenSSL
LDFLAGS = -lssl -lcrypto

# Файлы исходного кода
SRC = client.cpp

# Директории для заголовочных файлов
INCLUDE = -I./include

# Файлы объектных файлов
OBJ = $(SRC:.cpp=.o)

# Сборка всех исходников и линковка
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Сборка объектных файлов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# Очистка скомпилированных файлов
clean:
	rm -f $(OBJ) $(TARGET)

# Правило для запуска тестов
test: $(TARGET)
	./$(TARGET) # Здесь можно задать параметры запуска или сделать отдельный тестовый target

# Специальные цели
.PHONY: clean test

