#pragma once

#include <string>
#include <vector>

class Utils {
public:
    template <typename T>
    static std::string vec_to_str(const std::vector<T>& v);
};