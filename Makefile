# Name of your executable 
EXECUTABLE = out/pmf

# C++ compiler to use
CXX = g++

# C++ flags 
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Source files (adjust as needed)
SOURCES = src/Motor.cpp

# Object files (created during compilation)
OBJECTS = $(SOURCES:.cpp=.o)

# The default 'all' target (what happens when you type 'make')
all: $(EXECUTABLE)

# Rule to link object files into the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE) -llgpio

# Rule to compile individual .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

# 'clean' target for removing build artifacts
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)