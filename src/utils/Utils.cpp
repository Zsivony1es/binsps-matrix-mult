#include "Utils.h"

template <typename T>
std::string Utils::vec_to_str(const std::vector<T>& v){
    std::stringstream ss;
    ss << '[';
    bool first = true;
    std::for_each(std::begin(v), std::end(v),
               [&ss, &first, sep=""](T x) mutable {
                   ss << sep << x;
                   if (first){
                    first = false;
                    sep = ", ";
                   }
               });
    ss << ']';
    return ss.str();
}

uint Utils::time_exec(std::function<void()> func){
    
    auto start = std::chrono::steady_clock::now();
    func();
    auto end = std::chrono::steady_clock::now();

    return std::chrono::duration<double, std::nano>(end - start).count();
}