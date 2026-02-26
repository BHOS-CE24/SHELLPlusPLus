# Makefile for SHELL++
# Author: Vugar Ahadli (Vuq17)
# Date: 2026-02-11

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -O2 -Iinclude

# Directories
SRC_DIR := src
BIN_DIR := binaries

# Target executable
TARGET := shell++

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SRCS))

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files in binaries/
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure binaries directory exists
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean build artefacts
clean:
	rm -rf $(BIN_DIR)/*.o $(TARGET)

# Run the shell directly
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
