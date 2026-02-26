# Makefile for SHELL++
# Author: Vugar Ahadli (Vuq17)
# Date: 2026-02-11


CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -O2 -Iinclude


SRC_DIR := src
BIN_DIR := binaries


TARGET := shell++


SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SRCS))


all: $(TARGET)


$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^


$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


$(BIN_DIR):
	mkdir -p $(BIN_DIR)


clean:
	rm -rf $(BIN_DIR)/*.o $(TARGET)


run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
