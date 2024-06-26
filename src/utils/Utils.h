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
     * @brief Converts an unordered_map to a string representation.
     * @tparam T The type of the keys in the map.
     * @tparam U The type of the values in the map.
     * @param m The map to be converted.
     * @return The string representation of the map.
     */
    template <typename T, typename U>
    static std::string map_to_str(const std::unordered_map<T, U>& m);

    /**
     * @brief Writes a string to a file.
     * @param filename The name of the file to be written to.
     * @param content The content to be written to the file.
     */
    static void append_to_file(const std::string& filename, const std::string& content){
        std::ofstream file;
        file.open("./generated/" + filename,std::ios::app);
        file << content <<std::endl;
        file.close();
    }

    static inline void create_perf_test_header_if_not_exists(std::string filename = "performance_results.csv"){
        std::string performance_results_path = "./generated/" + filename;
        std::string header = "N,M,sparsity,naive_time,blas_time,opt_time,naive_speedup,blas_speedup,opt_speedup";
        std::ifstream f(performance_results_path.c_str());

        if (!f.good()) { // Check if file is already created
            std::ofstream file;
            file.open(performance_results_path, std::ios::app);
            file << header <<std::endl;
            file.close();
        }
    }

    static void create_multi_prod_perf_test_header_if_not_exists(){
        std::string performance_results_path = "./generated/multi_product_performance_results.csv";
        std::string header = "N,naive_time,blas_time,opt_time,ps_time,naive_speedup,opt_speedup,blas_speedup,ps_speedup";
        std::ifstream f(performance_results_path.c_str());

        if (!f.good()) { // Check if file is already created
            std::ofstream file;
            file.open(performance_results_path, std::ios::app);
            file << header <<std::endl;
            file.close();
        }
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
    static inline std::vector<double> generate_random_vector(size_t size, double min = 0.0, double max = 1.0){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(min, max);
        std::vector<double> vec(size);
        
        for (int i = 0; i < size; ++i) {
            vec[i] = dis(gen);
        }
        
        return vec;
    }

    static double round_to_n_digits(double value, int n = 2){
        return std::round(value * std::pow(10,n)) / std::pow(10,n);
    }

    static inline void test_debug(std::string str){
        std::cout << ANSI_TXT_GRN << "[   DEBUG  ] " << ANSI_TXT_DFT << str << std::endl;
    }
};