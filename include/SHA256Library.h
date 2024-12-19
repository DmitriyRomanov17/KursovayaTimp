/**
 * @file SHA256Library.h
 * @brief Header file for the SHA256Library class that provides functionality for computing SHA-256 hash.
 * 
 * This file defines the `SHA256Library` class, which contains the method to compute the 
 * SHA-256 hash of a given input string. The class implements the entire SHA-256 algorithm, 
 * including padding and the iterative computation of the hash.
 * 
 * @author Romanov D.E.
 * @date 2024-12-19
 */
#ifndef SHA256_LIBRARY_H
#define SHA256_LIBRARY_H

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstring>
/**
 * @class SHA256Library
 * @brief A class to compute SHA-256 hash for an input string.
 * 
 * The `SHA256Library` class provides a method to compute the SHA-256 hash of a string 
 * using the standard SHA-256 algorithm. The hashing process involves padding the input, 
 * processing it in chunks, and iterating over multiple rounds to produce the final hash.
 */
class SHA256Library {
public:
    /**
     * @brief Computes the SHA-256 hash of a given input string.
     * 
     * This method applies the SHA-256 algorithm to the input string, including necessary 
     * padding and iterative calculations, and returns the resulting hash as a hexadecimal string.
     * 
     * @param input The string to be hashed.
     * @return A string representing the SHA-256 hash of the input, in hexadecimal format.
     */
    static std::string hash(const std::string& input) {
        // Initial hash values
        uint32_t h[8] = {
            0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
            0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
        };

        // Predefined round constants
        uint32_t k[64] = {
            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
            0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
            0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
            0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
            0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
            0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
            0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
            0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
            0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
            0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
            0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
            0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
            0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
            0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
            0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
            0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
        };

        // Padding
        std::vector<uint8_t> padded;
        padded.insert(padded.end(), input.begin(), input.end());
        padded.push_back(0x80);

        while ((padded.size() + 8) % 64 != 0) {
            padded.push_back(0);
        }

        uint64_t bitLength = static_cast<uint64_t>(input.size()) * 8;
        for (int i = 0; i < 8; ++i) {
            padded.push_back((bitLength >> (56 - i * 8)) & 0xFF);
        }

        // Process chunks
        for (size_t chunk = 0; chunk < padded.size() / 64; ++chunk) {
            uint32_t w[64] = {0};
            for (int i = 0; i < 16; ++i) {
                w[i] = (padded[chunk * 64 + i * 4] << 24) |
                       (padded[chunk * 64 + i * 4 + 1] << 16) |
                       (padded[chunk * 64 + i * 4 + 2] << 8) |
                       (padded[chunk * 64 + i * 4 + 3]);
            }

            for (int i = 16; i < 64; ++i) {
                uint32_t s0 = rotateRight(w[i - 15], 7) ^ rotateRight(w[i - 15], 18) ^ (w[i - 15] >> 3);
                uint32_t s1 = rotateRight(w[i - 2], 17) ^ rotateRight(w[i - 2], 19) ^ (w[i - 2] >> 10);
                w[i] = w[i - 16] + s0 + w[i - 7] + s1;
            }

            uint32_t a = h[0], b = h[1], c = h[2], d = h[3];
            uint32_t e = h[4], f = h[5], g = h[6], h_var = h[7];

            for (int i = 0; i < 64; ++i) {
                uint32_t S1 = rotateRight(e, 6) ^ rotateRight(e, 11) ^ rotateRight(e, 25);
                uint32_t ch = (e & f) ^ (~e & g);
                uint32_t temp1 = h_var + S1 + ch + k[i] + w[i];
                uint32_t S0 = rotateRight(a, 2) ^ rotateRight(a, 13) ^ rotateRight(a, 22);
                uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
                uint32_t temp2 = S0 + maj;

                h_var = g;
                g = f;
                f = e;
                e = d + temp1;
                d = c;
                c = b;
                b = a;
                a = temp1 + temp2;
            }

            h[0] += a;
            h[1] += b;
            h[2] += c;
            h[3] += d;
            h[4] += e;
            h[5] += f;
            h[6] += g;
            h[7] += h_var;
        }

        std::ostringstream result;
        for (int i = 0; i < 8; ++i) {
            result << std::hex << std::setw(8) << std::setfill('0') << h[i];
        }

        return result.str();
    }

private:
    /**
     * @brief Rotates the bits of a 32-bit value to the right.
     * 
     * This helper function performs a bitwise rotation of a 32-bit value to the right 
     * by the specified number of bits.
     * 
     * @param value The 32-bit value to be rotated.
     * @param bits The number of bits to rotate.
     * @return The value after rotating the bits to the right.
     */
    static uint32_t rotateRight(uint32_t value, int bits) {
        return (value >> bits) | (value << (32 - bits));
    }
};

#endif // SHA256_LIBRARY_H

