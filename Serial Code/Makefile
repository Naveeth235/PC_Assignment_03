# Serial Brute Force PIN Cracker Makefile

# Compiler and flags
CC = gcc
CFLAGS = -O3 -Wall
LIBS = -lcrypto

# Target executable
TARGET = brute_serial
SOURCE = brute_serial.c

# Default target
all: $(TARGET)

# Compilation rule
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LIBS)

# Run test
test: $(TARGET)
	@echo "=== Running serial brute force ==="
	./$(TARGET) 7 7654322

# Run with custom parameters
run: $(TARGET)
	./$(TARGET) 7 7654322

# Clean build artifacts
clean:
	rm -f $(TARGET) $(TARGET).exe

# Check compiler
check:
	@echo "=== GCC Version ==="
	$(CC) --version

# Help target
help:
	@echo "Available targets:"
	@echo "  make          - Compile the serial program"
	@echo "  make test     - Run the program with test PIN"
	@echo "  make run      - Run the program (same as test)"
	@echo "  make clean    - Remove compiled binaries"
	@echo "  make check    - Verify GCC installation"
	@echo "  make help     - Show this help message"

.PHONY: all test run clean check help
