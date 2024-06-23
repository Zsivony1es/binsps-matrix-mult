#include <gtest/gtest.h>
#include <chrono>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>
#include <sstream>

#include "../src/RandomMatrixGenerator.cpp"
#include "../src/MatrixType.cpp"
#include "../src/MatrixProduct.cpp"

class DimensionPerformanceTests :
        public ::testing::Test{
protected:
    void SetUp() override {}

    void TearDown() override {}
};
