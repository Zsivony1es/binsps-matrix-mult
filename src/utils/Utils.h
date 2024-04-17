#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <functional>
#include <chrono>

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
};