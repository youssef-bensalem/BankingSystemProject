# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Find all .cpp files
SRCS := $(wildcard main.cpp) \
        $(wildcard src/*.cpp) \
        $(wildcard src/core/*.cpp) \
        $(wildcard src/system/*.cpp) \
        $(wildcard src/utils/*.cpp)

# Output binary
TARGET = main.exe

# Object files
OBJS := $(SRCS:.cpp=.o)

# Build rule
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Compile rule
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean command
clean:
	rm -f *.o src/core/*.o src/system/*.o src/utils/*.o main.exe