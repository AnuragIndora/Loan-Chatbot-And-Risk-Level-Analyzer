# Makefile for Loan Chatbot

CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -O2

TARGET = main
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.o

run: $(TARGET)
	./$(TARGET)
