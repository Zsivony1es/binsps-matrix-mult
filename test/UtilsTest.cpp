#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "../src/utils/Utils.cpp" // Ensure this path is correct

TEST(UtilsTest, test_vec_to_str_with_integers) {
    std::vector<int> vec = {1, 2, 3};
    std::string expected = "[1, 2, 3]";
    ASSERT_EQ(Utils::vec_to_str(vec), expected);
}

TEST(UtilsTest, test_vec_to_str_with_empty_vector) {
    std::vector<int> vec = {};
    std::string expected = "[]";
    ASSERT_EQ(Utils::vec_to_str(vec), expected);
}

TEST(UtilsTest, test_vec_to_str_with_string_vector) {
    std::vector<std::string> vec = {"hello", "world"};
    std::string expected = "[hello, world]";
    ASSERT_EQ(Utils::vec_to_str(vec), expected);
}

// main function to run the tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
