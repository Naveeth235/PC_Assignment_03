# OpenMP Brute Force PIN Cracker Makefile

# Compiler and flags
CC = gcc
CFLAGS = -O3 -Wall -fopenmp
LIBS = -lcrypto

# Target executable
TARGET = brute_openmp
SOURCE = brute_OpenMP.c

# Default target
all: $(TARGET)

# Compilation rule
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LIBS)

# Run with different thread counts
test: $(TARGET)
	@echo "=== Running with 1 thread ==="
	OMP_NUM_THREADS=1 ./$(TARGET) 7 9876543
	@echo ""
	@echo "=== Running with 2 threads ==="
	OMP_NUM_THREADS=2 ./$(TARGET) 7 9876543
	@echo ""
	@echo "=== Running with 4 threads ==="
	OMP_NUM_THREADS=4 ./$(TARGET) 7 9876543
	@echo ""
	@echo "=== Running with 8 threads ==="
	OMP_NUM_THREADS=8 ./$(TARGET) 7 9876543
	@echo ""
	@echo "=== Running with 16 threads ==="
	OMP_NUM_THREADS=16 ./$(TARGET) 7 9876543

# Run single test
run: $(TARGET)
	OMP_NUM_THREADS=4 ./$(TARGET) 7 9876543

# Clean build artifacts
clean:
	rm -f $(TARGET) $(TARGET).exe

# Check OpenMP support
check:
	@echo "=== GCC Version ==="
	$(CC) --version
	@echo ""
	@echo "=== OpenMP Support ==="
	@echo "Compiling test program..."
	@echo '#include <omp.h>' > /tmp/omp_test.c
	@echo 'int main() { return omp_get_max_threads(); }' >> /tmp/omp_test.c
	@$(CC) -fopenmp /tmp/omp_test.c -o /tmp/omp_test && echo "OpenMP is supported!" || echo "OpenMP not available"
	@rm -f /tmp/omp_test.c /tmp/omp_test

# Help target
help:
	@echo "Available targets:"
	@echo "  make          - Compile the OpenMP program"
	@echo "  make test     - Run all thread count tests (1, 2, 4, 8, 16)"
	@echo "  make run      - Run single test with 4 threads"
	@echo "  make clean    - Remove compiled binaries"
	@echo "  make check    - Verify GCC and OpenMP support"
	@echo "  make help     - Show this help message"

.PHONY: all test run clean check help
