# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Target executable file
TARGET = main.out

# Source files
SRC = HashTable.cpp main.cpp

# Default rule to build the executable
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean up generated files
clean:
	rm -f $(TARGET)
