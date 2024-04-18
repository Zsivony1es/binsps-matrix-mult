#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "../src/utils/Utils.h" // Assuming Utils.h contains the declaration of Utils class and vec_to_str method

class UtilsTest : public ::testing::Test {

};

TEST_F(UtilsTest, test_vec_to_str_with_integers) {
    std::vector<int> vec = {1, 2, 3};
    std::string expected = "[1, 2, 3]";
    ASSERT_EQ(Utils::vec_to_str(vec), expected);
}

TEST_F(UtilsTest, test_vec_to_str_with_empty_vector) {
    std::vector<int> vec = {};
    std::string expected = "[]";
    ASSERT_EQ(Utils::vec_to_str(vec), expected);
}

TEST_F(UtilsTest, test_vec_to_str_with_string_vector) {
    std::vector<std::string> vec = {"hello", "world"};
    std::string expected = "[hello, world]";
    ASSERT_EQ(Utils::vec_to_str(vec), expected);
}