#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <functional>
#include <chrono>
#include <fstream>
#include <random>
#include <iostream>

#define ANSI_TXT_GRN "\033[0;32m"
#define ANSI_TXT_MGT "\033[0;35m"
#define ANSI_TXT_DFT "\033[0;0m" // Console default

/**
 * @brief The Utils class provides utility functions for various operations.
 */
class Utils {
public:
    /**
     * @brief Converts a vector to a string representation.
     * @tparam T The type of elements in the vector.
     * @param v The vector to be converted.
     * @return The string representation of the vector.
     */
    template <typename T>
    static std::string vec_to_str(const std::vector<T>& v);

    /**
     * @brief Writes a string to a file.
     * @param filename The name of the file to be written to.
     * @param content The content to be written to the file.
     */
    static void write_to_file(const std::string& filename, const std::string& content){
        std::ofstream file;
        file.open("./generated/" + filename,std::ios::app);
        file << content <<std::endl;
        file.close();
    }

    /**
     * @brief Measures the execution time of a given function.
     * @param func The function to be executed.
     * @return The execution time in nanoseconds.
     */
    static inline uint time_exec(std::function<void(void)> func){
        auto start = std::chrono::steady_clock::now();
        func();
        auto end = std::chrono::steady_clock::now();

        return std::chrono::duration<double, std::nano>(end - start).count();
    }

    /**
     * Generates a random vector of doubles.
     *
     * @return A vector of doubles containing random values between 1 and 100.
     */
    static inline std::vector<double> generate_random_vector(size_t size){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(1, 10); // Adjust range as needed
        std::vector<double> vec(size);
        
        for (int i = 0; i < size; ++i) {
            vec[i] = dis(gen);
        }
        
        return vec;
    }

    static inline void test_debug(std::string str){
        std::cout << ANSI_TXT_GRN << "[   DEBUG  ] " << ANSI_TXT_DFT << str << std::endl;
    }
};