# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Find all source files in the current directory
SOURCES = $(wildcard *.cpp)

# Create object file names
OBJECTS = $(SOURCES:.cpp=.o)

# The target executable
TARGET = my_program

# Default target to build the program
all: $(TARGET)

# Link object files into the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile each .cpp file into a .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean object files and the executable
clean:
	rm -f $(OBJECTS) $(TARGET)

# Phony targets
.PHONY: all clean
