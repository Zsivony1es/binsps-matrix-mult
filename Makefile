# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -std=c++2b

# Directories
SRC_DIR := src
TEST_DIR := test

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/**/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(SRC_DIR)/%.o, $(SRCS)) main.o

TEST_SRCS := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.cpp, $(TEST_DIR)/%.o, $(TEST_SRCS))

# Google Test library and flags
GTEST_DIR := /opt/homebrew/opt/googletest
GTEST_INCLUDE := -I$(GTEST_DIR)/include
GTEST_LIB := -L$(GTEST_DIR)/lib -lgtest -lgtest_main -pthread

# Executables
TARGET := run
TEST_TARGET := run_tests

.PHONY: all test clean

all: $(TARGET)

# Main target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Test target
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS) $(filter-out main.o, $(OBJS))
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

# Compile rules for source files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile rules for test files
$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(GTEST_INCLUDE) -c -o $@ $<

# Compilation for main.o
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(TEST_TARGET) $(SRC_DIR)/**/*.o $(SRC_DIR)/*.o $(TEST_DIR)/*.o $(TEST_DIR)/**/*.o main.o
