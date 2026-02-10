# Makefile for shell++
# Author: Vugar Ahadli (Vuq17)
# Date: 2026-02-11

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -O2

# Target executable
TARGET := shell++

# Source files
SRCS := main.cpp tokenizer.cpp builtins.cpp

# Object files
OBJS := $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp files to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artefacts
clean:
	rm -f $(OBJS) $(TARGET)

# Run the shell directly
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
