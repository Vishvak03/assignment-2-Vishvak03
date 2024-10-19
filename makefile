# Specify the compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Target executable
TARGET = main.out

# Source files
SRC = main.cpp HashTable.cpp

# Default build rule
all: $(TARGET)

# Rule to create the executable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean rule to remove the generated executable
clean:
	rm -f $(TARGET)
