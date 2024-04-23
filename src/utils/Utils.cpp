#include "Utils.h"

/**
  * @brief Converts a vector to a string representation.
  * @tparam T The type of elements in the vector.
  * @param v The vector to be converted.
  * @return The string representation of the vector.
*/
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
