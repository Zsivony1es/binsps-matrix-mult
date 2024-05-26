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

/**
 * @brief Converts an unordered_map to a string representation.
 * @tparam T The type of the keys in the map.
 * @tparam U The type of the values in the map.
 * @param m The map to be converted.
 * @return The string representation of the map.
 */
template <typename T, typename U>
std::string Utils::map_to_str(const std::unordered_map<T, U>& m){
    std::stringstream ss;
    ss << '{';
    bool first = true;
    std::for_each(std::begin(m), std::end(m),
               [&ss, &first, sep=""](const std::pair<T, U>& p) mutable {
                   ss << sep << '(' << p.first << ": " << p.second << ')';
                   if (first){
                    first = false;
                    sep = ", ";
                   }
               });
    ss << '}';
    return ss.str();
}