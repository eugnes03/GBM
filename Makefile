# Compiler
CXX = c++

# Compiler flags
CXXFLAGS = -Wall -g

# Target executable
TARGET = build/simulate

# For deleting the target
TARGET_DEL = build/simulate

# Source files
SRCS = apps/simulate.cpp src/gbm.cpp src/csv.cpp src/black_scholes.cpp src/monte_carlo.cpp
# Object files
OBJS = $(SRCS:.cpp=.o)

# Default rule to build and run the executable
all: $(TARGET) run


# Rule to link object files into the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -Iinclude -c $< -o $@

# Rule to run the executable
run: $(TARGET)
	$(TARGET)

# Clean rule to remove generated files
clean:
	rm $(TARGET_DEL) $(OBJS)
