#include <iostream>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>
#include <string>
#include <fstream>

constexpr int DEFAULT_PORT = 33333;
constexpr size_t SALT_SIZE = 16;
constexpr size_t HASH_SIZE = SHA256_DIGEST_LENGTH;

// Хеширование строки с солью
std::string hash_with_salt(const std::string& salt, const std::string& password) {
    std::string salted_input = salt + password;
    unsigned char hash[HASH_SIZE];
    SHA256(reinterpret_cast<const unsigned char*>(salted_input.c_str()), salted_input.size(), hash);

    std::ostringstream oss;
    oss << std::uppercase;
    for (unsigned char c : hash) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    }
    return oss.str();
}

// Аутентификация с сервером
bool authenticate(int socket, const std::string& login, const std::string& password) {
    // Отправляем login
    if (send(socket, login.c_str(), login.size(), 0) <= 0) {
        std::cerr << "Error: Failed to send login.\n";
        return false;
    }

    // Получаем соль от сервера
    char salt_buffer[SALT_SIZE + 1] = {0};
    if (recv(socket, salt_buffer, SALT_SIZE, 0) <= 0) {
        std::cerr << "Error: Failed to receive salt.\n";
        return false;
    }
    std::string salt(salt_buffer);
    if (salt == "ERR") {
        std::cerr << "Authentication error: Server responded with ERR.\n";
        return false;
    }

    // Вычисляем хеш и отправляем его на сервер
    std::string hash = hash_with_salt(salt, password);
    if (send(socket, hash.c_str(), hash.size(), 0) <= 0) {
        std::cerr << "Error: Failed to send hash.\n";
        return false;
    }

    // Получаем ответ сервера
    char auth_response[3] = {0};
    if (recv(socket, auth_response, 2, 0) <= 0) {
        std::cerr << "Error: Failed to receive auth response.\n";
        return false;
    }
    return std::string(auth_response) == "OK";
}

// Отправка векторов на сервер и получение результата
void send_vectors(int socket, const std::vector<std::vector<double>>& vectors) {
    uint16_t num_vectors = vectors.size();

    if (send(socket, &num_vectors, sizeof(num_vectors), 0) != sizeof(num_vectors)) {
        std::cerr << "Error: Failed to send number of vectors.\n";
        return;
    }

    for (const auto& vec : vectors) {
        uint16_t vec_size = vec.size();
        if (send(socket, &vec_size, sizeof(vec_size), 0) != sizeof(vec_size)) {
            std::cerr << "Error: Failed to send vector size.\n";
            return;
        }
        size_t data_size = vec.size() * sizeof(double);
        if (static_cast<size_t>(send(socket, vec.data(), data_size, 0)) != data_size) {
            std::cerr << "Error: Failed to send vector data.\n";
            return;
        }

        double result;
        if (recv(socket, &result, sizeof(result), 0) != sizeof(result)) {
            std::cerr << "Error: Failed to receive result.\n";
            return;
        }
        std::cout << "Result for vector: " << result << "\n";
    }
}

// Основная функция клиента
int main(int argc, char* argv[]) {
    if (argc < 5) {
        std::cerr << "Usage: " << argv[0] << " <server_address> <port> <input_file> <login_file> <output_file>\n";
        return 1;
    }

    std::string server_address = argv[1];
    int port = std::stoi(argv[2]);
    std::string input_file = argv[3];
    std::string login_file = argv[4];
    std::string output_file = argv[5];

    // Чтение данных логина
    std::ifstream login_data(login_file);
    if (!login_data) {
        std::cerr << "Error: Unable to open login file.\n";
        return 1;
    }

    std::string login, password;
    login_data >> login >> password;

    // Создание и подключение сокета
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, server_address.c_str(), &server_addr.sin_addr);


    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        return 1;
    }

    // Аутентификация
    if (!authenticate(sock, login, password)) {
        std::cerr << "Authentication failed.\n";
        close(sock);
        return 1;
    }

    // Чтение и отправка векторов
    std::ifstream data_file(input_file, std::ios::binary);
    if (!data_file) {
        std::cerr << "Error: Unable to open input file.\n";
        close(sock);
        return 1;
    }

    uint16_t vector_count;
    data_file >> vector_count;

    std::vector<std::vector<double>> vectors;
    for (int i = 0; i < vector_count; ++i) {
        uint16_t vec_size;
        data_file >> vec_size;
        std::vector<double> vec(vec_size);
        for (int j = 0; j < vec_size; ++j) {
            data_file >> vec[j];
        }
        vectors.push_back(vec);
    }


    send_vectors(sock, vectors);

    close(sock);
    return 0;
}

