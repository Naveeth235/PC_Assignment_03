/*
 * brute_MPI.c
 * MPI Parallel brute-force SHA-256 PIN cracking
 *
 * Compile:
 * mpicc -O3 -o brute_mpi brute_MPI.c -lcrypto
 *
 * Run:
 * mpirun -np 4 ./brute_mpi 7 9876438
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <mpi.h>

#define CHECK_INTERVAL 2500   // Check for stop signals every 2500 iterations

// PIN generator
void generate_pin(unsigned long long num, int len, char *buffer) {
    for (int i = len - 1; i >= 0; i--) {
        buffer[i] = (num % 10) + '0';
        num /= 10;
    }
    buffer[len] = '\0';
}

// Return SHA-256 hex string
void sha256_hex(const unsigned char *input, size_t len, char outhex[65]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(input, len, hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        sprintf(outhex + (i * 2), "%02x", hash[i]);

    outhex[64] = '\0';
}

int main(int argc, char *argv[]) {

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Argument check
    if (argc != 3) {
        if (rank == 0) {
            printf("Usage: mpirun -np N ./brute_mpi <pin_length> <plaintext_pin>\n");
            printf("Example: mpirun -np 4 ./brute_mpi 4 0420\n");
        }
        MPI_Finalize();
        return 1;
    }

    int pin_len = atoi(argv[1]);
    const char *target_plain = argv[2];

    // Compute the target SHA-256 ONCE, then broadcast result
    char target_hash[65];

    if (rank == 0) {
        sha256_hex((const unsigned char*)target_plain, strlen(target_plain), target_hash);
        
        printf("Target: %s\n", target_plain);
        printf("Hash:   %s\n", target_hash);
        printf("Starting MPI crack with %d processes...\n", size);
    }

    // Broadcast target hash to all MPI ranks
    MPI_Bcast(target_hash, 65, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Compute PIN search space: 10^pin_len
    unsigned long long max = 1;
    for (int i = 0; i < pin_len; i++) max *= 10ULL;

    char candidate[32];
    char hashhex[65];

    int stop_flag = 0;    // Received STOP from another rank?
    int found = 0;        // Did THIS rank find the PIN?

    // Asynchronous receive for stop signal
    MPI_Request stop_request;
    MPI_Irecv(&stop_flag, 1, MPI_INT, MPI_ANY_SOURCE, 999, MPI_COMM_WORLD, &stop_request);

    double t0 = MPI_Wtime();

    // Cyclic Distribution: i = rank, rank+size, rank+2*size, ...
    for (unsigned long long i = rank; i < max; i += size) {

        // Check infrequently to reduce overhead
        if (i % CHECK_INTERVAL == 0) {
            int chk = 0;
            MPI_Test(&stop_request, &chk, MPI_STATUS_IGNORE);
            if (chk) break; // Another rank found the solution
        }

        // Fast candidate generation
        generate_pin(i, pin_len, candidate);

        // Hash candidate
        sha256_hex((unsigned char*)candidate, pin_len, hashhex);

        // Compare hashes
        if (strcmp(hashhex, target_hash) == 0) {
            found = 1;

            double t1 = MPI_Wtime();
            
            printf("FOUND! Candidate: %s (Rank %d)\n", candidate, rank);
            printf("Time taken: %.4f s\n", t1 - t0);

            // Notify everyone else
            int msg = 1;
            MPI_Request send_req;
            for (int p = 0; p < size; p++) {
                if (p != rank) {
                    MPI_Isend(&msg, 1, MPI_INT, p, 999, MPI_COMM_WORLD, &send_req);
                }
            }
            break;
        }
    }

    // Cleanup: cancel outstanding receive if not used
    int completed = 0;
    MPI_Test(&stop_request, &completed, MPI_STATUS_IGNORE);
    if (!completed)
        MPI_Cancel(&stop_request);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}