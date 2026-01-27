# -----------------------------
# Compiler & flags
# -----------------------------
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic

# Build modes
DEBUG_FLAGS := -O0 -g
RELEASE_FLAGS := -O3

# -----------------------------
# Targets
# -----------------------------
TARGET := engine
SRC := main.cpp
OBJ := $(SRC:.cpp=.o)

# Default build
all: release

# -----------------------------
# Debug build
# -----------------------------
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

# -----------------------------
# Release build
# -----------------------------
release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

# -----------------------------
# Link
# -----------------------------
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# -----------------------------
# Compile
# -----------------------------
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# -----------------------------
# Utilities
# -----------------------------
clean:
	rm -f $(OBJ) $(TARGET) *.exe

.PHONY: all debug release clean
