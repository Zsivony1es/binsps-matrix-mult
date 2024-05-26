#pragma GCC diagnostic ignored "-Wpragma-once-outside-header"
#pragma once

#include <cstdlib>
#include <string>

template <typename T>
struct IMatrix {
    virtual ~IMatrix() = default;
    virtual const T operator[](size_t row, size_t col) const = 0;
    virtual std::string to_string() const = 0;
};
