# CUDA Brute Force PIN Cracker Makefile

# Compiler and flags
NVCC = nvcc
CUDA_ARCH = -gencode arch=compute_75,code=sm_75
LIBS = -lssl -lcrypto
CFLAGS = -O3

# Target executable
TARGET = brute_cuda
SOURCE = brute_cuda.cu

# Default target
all: $(TARGET)

# Compilation rule
$(TARGET): $(SOURCE)
	$(NVCC) $(SOURCE) -o $(TARGET) $(LIBS) $(CUDA_ARCH) $(CFLAGS)

# Run with different thread counts
test: $(TARGET)
	@echo "=== Running with 1 thread ==="
	./$(TARGET) 7 7654322 1
	@echo ""
	@echo "=== Running with 2 threads ==="
	./$(TARGET) 7 7654322 2
	@echo ""
	@echo "=== Running with 4 threads ==="
	./$(TARGET) 7 7654322 4
	@echo ""
	@echo "=== Running with 8 threads ==="
	./$(TARGET) 7 7654322 8
	@echo ""
	@echo "=== Running with 16 threads ==="
	./$(TARGET) 7 7654322 16

# Run single test
run: $(TARGET)
	./$(TARGET) 7 7654322 16

# Clean build artifacts
clean:
	rm -f $(TARGET) $(TARGET).exe

# Check CUDA installation
check:
	@echo "=== CUDA GPU Information ==="
	nvidia-smi
	@echo ""
	@echo "=== NVCC Version ==="
	nvcc --version

# Help target
help:
	@echo "Available targets:"
	@echo "  make          - Compile the CUDA program"
	@echo "  make test     - Run all thread count tests (1, 2, 4, 8, 16)"
	@echo "  make run      - Run single test with 16 threads"
	@echo "  make clean    - Remove compiled binaries"
	@echo "  make check    - Verify CUDA installation and GPU info"
	@echo "  make help     - Show this help message"

.PHONY: all test run clean check help
