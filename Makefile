# Variables
CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 \
           -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference \
           -g3 -O0 -MMD -MP
BUILD_DIR = build/Debug
TARGET = $(BUILD_DIR)/outDebug
SRCS = $(wildcard *.cpp) # Finds all .cpp files in the directory
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o) # Maps .cpp files to .o files
DEPS = $(OBJS:.o=.d) # Maps .o files to .d dependency files

# Default target
all: $(TARGET)

# Build target executable
$(TARGET): $(OBJS)
	@echo "Linking target: $(TARGET)"
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Rule for building object files
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(BUILD_DIR) # Create build directory if it doesn't exist
	@echo "Compiling: $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include dependency files to track header dependencies
-include $(DEPS)

# Clean target to remove build files
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)
