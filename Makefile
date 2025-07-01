# Makefile for OOP-based Loan Chatbot

CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -O2 -Iinclude

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/chatbot

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

# Default target
all: $(TARGET)

# Link object files
$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) chatlog.txt output_with_risk.csv

# Run the chatbot
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
