#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <functional>
#include <time.h>

class Utils {
public:
    template <typename T>
    static std::string vec_to_str(const std::vector<T>& v);
    static uint time_exec(std::function<void()> func);
};