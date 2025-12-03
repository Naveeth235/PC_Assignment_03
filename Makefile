# Root Makefile for Parallel Computing Final Assignment
# Builds all implementations: Serial, OpenMP, MPI, and CUDA

.PHONY: all serial openmp mpi cuda clean test help

# Default: build all
all: serial openmp mpi cuda

# Build individual implementations
serial:
	@echo "=== Building Serial Implementation ==="
	$(MAKE) -C "Serial Code"
	@echo ""

openmp:
	@echo "=== Building OpenMP Implementation ==="
	$(MAKE) -C "OpenMP Code"
	@echo ""

mpi:
	@echo "=== Building MPI Implementation ==="
	$(MAKE) -C "MPI Code"
	@echo ""

cuda:
	@echo "=== Building CUDA Implementation ==="
	$(MAKE) -C "CUDA Code"
	@echo ""

# Run all tests
test: all
	@echo "========================================="
	@echo "Testing Serial Implementation"
	@echo "========================================="
	$(MAKE) -C "Serial Code" test
	@echo ""
	@echo "========================================="
	@echo "Testing OpenMP Implementation"
	@echo "========================================="
	$(MAKE) -C "OpenMP Code" test
	@echo ""
	@echo "========================================="
	@echo "Testing MPI Implementation"
	@echo "========================================="
	$(MAKE) -C "MPI Code" test
	@echo ""
	@echo "========================================="
	@echo "Testing CUDA Implementation"
	@echo "========================================="
	$(MAKE) -C "CUDA Code" test
	@echo ""
	@echo "========================================="
	@echo "All tests completed!"
	@echo "========================================="

# Clean all build artifacts
clean:
	@echo "Cleaning all implementations..."
	$(MAKE) -C "Serial Code" clean
	$(MAKE) -C "OpenMP Code" clean
	$(MAKE) -C "MPI Code" clean
	$(MAKE) -C "CUDA Code" clean
	@echo "Clean complete!"

# Check all environments
check:
	@echo "=== Checking Serial (GCC) ==="
	$(MAKE) -C "Serial Code" check
	@echo ""
	@echo "=== Checking OpenMP ==="
	$(MAKE) -C "OpenMP Code" check
	@echo ""
	@echo "=== Checking MPI ==="
	$(MAKE) -C "MPI Code" check
	@echo ""
	@echo "=== Checking CUDA ==="
	$(MAKE) -C "CUDA Code" check

# Help message
help:
	@echo "Parallel Computing Final Assignment - Build System"
	@echo "=================================================="
	@echo ""
	@echo "Available targets:"
	@echo "  make              - Build all implementations (serial, openmp, mpi, cuda)"
	@echo "  make serial       - Build only serial implementation"
	@echo "  make openmp       - Build only OpenMP implementation"
	@echo "  make mpi          - Build only MPI implementation"
	@echo "  make cuda         - Build only CUDA implementation"
	@echo "  make test         - Build and run all tests"
	@echo "  make clean        - Remove all compiled binaries"
	@echo "  make check        - Verify all compiler installations"
	@echo "  make help         - Show this help message"
	@echo ""
	@echo "Individual implementation commands:"
	@echo "  cd 'Serial Code' && make help"
	@echo "  cd 'OpenMP Code' && make help"
	@echo "  cd 'MPI Code' && make help"
	@echo "  cd 'CUDA Code' && make help"
