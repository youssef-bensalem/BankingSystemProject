# Compiler (MinGW recommended for Windows portability)
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Static link to avoid missing DLLs on Windows
LDFLAGS = -static -static-libgcc -static-libstdc++ 

# Source directories
SRC_DIRS := . src src/core src/system src/utils

# Collect all .cpp files from those directories
SRCS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))

# Convert .cpp → .o
OBJS := $(SRCS:.cpp=.o)

# Target executable
TARGET = main.exe

# Default build
all: $(TARGET)

# Link binary
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile rule
%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(TARGET) $(OBJS)
