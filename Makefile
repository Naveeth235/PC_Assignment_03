# Root Makefile for Parallel Computing Final Assignment
# Builds all implementations: Serial, OpenMP, MPI, and CUDA

.PHONY: all serial openmp mpi cuda clean test help

# Default: build all (excluding CUDA - run on Google Colab)
all: serial openmp mpi

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
	@echo "⚠️  CUDA implementation should be run on Google Colab"
	@echo "⚠️  Open CUDA Code/brute_CUDA.ipynb in Google Colab"
	@echo ""

# Run all tests (excluding CUDA)
test: serial openmp mpi
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
	@echo "CUDA Implementation"
	@echo "========================================="
	@echo "⚠️  CUDA should be tested on Google Colab"
	@echo "⚠️  Open CUDA Code/brute_CUDA.ipynb in Google Colab"
	@echo ""
	@echo "========================================="
	@echo "Local tests completed!"
	@echo "========================================="

# Clean all build artifacts
clean:
	@echo "Cleaning local implementations..."
	$(MAKE) -C "Serial Code" clean
	$(MAKE) -C "OpenMP Code" clean
	$(MAKE) -C "MPI Code" clean
	@echo "Local clean complete!"
	@echo "⚠️  CUDA artifacts (if any) should be cleaned in Google Colab"

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
	@echo "⚠️  CUDA should be checked in Google Colab environment"

# Help message
help:
	@echo "Parallel Computing Final Assignment - Build System"
	@echo "=================================================="
	@echo ""
	@echo "Available targets:"
	@echo "  make              - Build local implementations (serial, openmp, mpi)"
	@echo "  make serial       - Build only serial implementation"
	@echo "  make openmp       - Build only OpenMP implementation"
	@echo "  make mpi          - Build only MPI implementation"
	@echo "  make cuda         - Show CUDA instructions (run on Google Colab)"
	@echo "  make test         - Build and run all local tests"
	@echo "  make clean        - Remove all compiled binaries"
	@echo "  make check        - Verify local compiler installations"
	@echo "  make help         - Show this help message"
	@echo ""
	@echo "CUDA Implementation:"
	@echo "  ⚠️  Run CUDA Code/brute_CUDA.ipynb on Google Colab"
	@echo ""
	@echo "Individual implementation commands:"
	@echo "  cd 'Serial Code' && make help"
	@echo "  cd 'OpenMP Code' && make help"
	@echo "  cd 'MPI Code' && make help"
	@echo "  cd 'CUDA Code' && make help"
