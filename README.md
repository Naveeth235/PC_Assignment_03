# Parallel Computing Assignment 03 - Brute Force PIN Cracker

## Project Overview

This project implements a **brute-force PIN cracking system** using SHA-256 hash comparison across multiple parallel computing paradigms. The system attempts to crack numeric PINs by generating all possible combinations and comparing their SHA-256 hashes with a target hash.

### Implementations

The project includes **four different implementations**:

1. **Serial Implementation** - Single-threaded baseline using standard C
2. **OpenMP Implementation** - Shared-memory parallelization using OpenMP
3. **MPI Implementation** - Distributed-memory parallelization using Message Passing Interface
4. **CUDA Implementation** - GPU-accelerated parallel processing using NVIDIA CUDA


## Prerequisites

### For Local Development (Windows)

1. **Make Build System**
   ```powershell
   # Using Chocolatey (run as Administrator)
   choco install make
   
   # Or using winget
   winget install GnuWin32.Make
   ```

2. **GCC Compiler** (for Serial and OpenMP)
   ```powershell
   # Using Chocolatey
   choco install mingw
   
   # Or install TDM-GCC or Dev-C++
   ```

3. **OpenSSL Development Libraries**
   ```powershell
   # Using vcpkg (recommended)
   vcpkg install openssl:x64-windows
   
   # Or using Chocolatey
   choco install openssl
   ```

4. **OpenMP Support**
   - Usually included with GCC
   - Verify with: `gcc -fopenmp --version`

5. **MPI Implementation**
   ```powershell
   # Microsoft MPI (recommended for Windows)
   # Download from: https://www.microsoft.com/en-us/download/details.aspx?id=57467
   
   # Or using Chocolatey
   choco install msmpi
   ```

### For CUDA Development

**CUDA implementation requires Google Colab or a system with NVIDIA GPU:**

- NVIDIA GPU with CUDA Compute Capability 3.0+
- CUDA Toolkit 11.0+
- NVIDIA Driver 450.80.02+

## Compilation Instructions

### Using Master Makefile

**Build all local implementations:**
```bash
make all
# or simply
make
```

**Build individual implementations:**
```bash
make serial    # Build serial version only
make openmp    # Build OpenMP version only
make mpi       # Build MPI version only
```

**Build and test all implementations:**
```bash
make test
```

### Alternative: Manual Compilation

If you don't have `make` installed, you can compile manually:

#### Serial Implementation
```bash
cd "Serial Code"
gcc -O3 -Wall -o brute_serial brute_serial.c -lcrypto
```

#### OpenMP Implementation
```bash
cd "OpenMP Code"
gcc -O3 -Wall -fopenmp -o brute_openmp brute_OpenMP.c -lcrypto
```

#### MPI Implementation
```bash
cd "MPI Code"
mpicc -O3 -o brute_mpi brute_MPI.c -lcrypto
```

#### CUDA Implementation
```bash
# Run on Google Colab
# Open CUDA Code/brute_CUDA.ipynb in Google Colab
# Execute the cells sequentially
```

## Execution Instructions

### Running Individual Implementations

#### 1. Serial Implementation
```bash
cd "Serial Code"
./brute_serial <pin_length> <target_password>

# Example:
./brute_serial 7 9876543
```

#### 2. OpenMP Implementation
```bash
cd "OpenMP Code"
./brute_openmp <pin_length> <target_password>

# Example:
./brute_openmp 7 9876543

# Set number of threads (optional):
export OMP_NUM_THREADS=4
./brute_openmp 7 9876543
```

#### 3. MPI Implementation
```bash
cd "MPI Code"
mpirun -np <num_processes> ./brute_mpi <pin_length> <target_password>

# Example with 4 processes:
mpirun -np 4 ./brute_mpi 7 9876543
```

#### 4. CUDA Implementation
```bash
# Upload brute_CUDA.ipynb to Google Colab
# Run all cells in sequence
# The notebook includes test cases and performance analysis
```

### Quick Test Run

**Test all local implementations:**
```bash
make test
```

This will:
1. Build all implementations (Serial, OpenMP, MPI)
2. Run each with test PIN: `7 9876543`
3. Display performance results


## Performance Analysis

The project allows comparison of different parallelization approaches:

- **Serial**: Baseline single-threaded performance
- **OpenMP**: Shared-memory parallelization efficiency
- **MPI**: Distributed computing scalability
- **CUDA**: GPU acceleration benefits


## Troubleshooting

### Common Issues

1. **"make: command not found"**
   ```powershell
   # Install make using chocolatey
   choco install make
   ```

2. **OpenSSL library not found**
   ```bash
   # Install OpenSSL development packages
   # Windows: Use vcpkg or precompiled binaries
   ```

3. **OpenMP not supported**
   ```bash
   # Use GCC instead of MSVC
   gcc -fopenmp --version
   ```

4. **MPI not found**
   ```powershell
   # Install Microsoft MPI
   # Add MPI to system PATH
   ```

5. **CUDA compilation fails**
   ```bash
   # Use Google Colab for CUDA implementation
   # Local CUDA requires NVIDIA GPU and CUDA Toolkit
   ```

### Environment Verification

Check your environment setup:
```bash
make check  # Verify all local compilers
```

## File Descriptions

- **`brute_serial.c`**: Sequential brute-force implementation
- **`brute_OpenMP.c`**: Parallel implementation using OpenMP directives
- **`brute_MPI.c`**: Distributed implementation using MPI communication
- **`brute_CUDA.ipynb`**: GPU implementation in Jupyter notebook format
- **`Makefile`** (in each directory): Build configuration for each implementation

## Academic Information

**Course**: SE3082 - Parallel Computing  
**Assignment**: Assignment 03  
**Date**: December 2025
