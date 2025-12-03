# MPI Brute Force PIN Cracker Makefile

# Compiler and flags
MPICC = mpicc
CFLAGS = -O3 -Wall
LIBS = -lcrypto

# Target executable
TARGET = brute_mpi
SOURCE = brute_MPI.c

# Default target
all: $(TARGET)

# Compilation rule
$(TARGET): $(SOURCE)
	$(MPICC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LIBS)

# Run with different process counts
test: $(TARGET)
	@echo "=== Running with 1 process ==="
	mpirun -np 1 ./$(TARGET) 7 9876438
	@echo ""
	@echo "=== Running with 2 processes ==="
	mpirun -np 2 ./$(TARGET) 7 9876438
	@echo ""
	@echo "=== Running with 4 processes ==="
	mpirun -np 4 ./$(TARGET) 7 9876438
	@echo ""
	@echo "=== Running with 8 processes ==="
	mpirun -np 8 ./$(TARGET) 7 9876438

# Run single test
run: $(TARGET)
	mpirun -np 4 ./$(TARGET) 7 9876438

# Clean build artifacts
clean:
	rm -f $(TARGET) $(TARGET).exe

# Check MPI installation
check:
	@echo "=== MPI Compiler Version ==="
	$(MPICC) --version
	@echo ""
	@echo "=== MPI Run Version ==="
	mpirun --version

# Help target
help:
	@echo "Available targets:"
	@echo "  make          - Compile the MPI program"
	@echo "  make test     - Run all process count tests (1, 2, 4, 8)"
	@echo "  make run      - Run single test with 4 processes"
	@echo "  make clean    - Remove compiled binaries"
	@echo "  make check    - Verify MPI installation"
	@echo "  make help     - Show this help message"

.PHONY: all test run clean check help
