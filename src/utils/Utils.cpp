#include "Utils.h"

<template typename T>
static std::string Utils::vec_to_str(const std::vector<T>& v){
    std::stringstream ss;
    ss << '[';
    bool first = true;
    std::for_each(std::begin(this->entries), std::end(this->entries),
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