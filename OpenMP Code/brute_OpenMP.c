// brute_OpenMP.c
// Parallel brute-force SHA-256 simulation over numeric PINs using OpenMP.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>
#include <omp.h> // OpenMP header

// Convert input string → SHA-256 → hex string
void sha256_hex(const unsigned char *input, size_t len, char outhex[65]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];

    // Calculate SHA-256
    SHA256(input, len, hash);

    // Convert each byte to 2-digit hex
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        sprintf(outhex + (i * 2), "%02x", hash[i]);

    outhex[64] = 0; // Null-terminate
}

int main(int argc, char *argv[]) {

    // Input validation
    if (argc < 3) {
        printf("Usage: %s <pin_length> <target_password>\n", argv[0]);
        return 1;
    }

    int pin_len = atoi(argv[1]);
    if (pin_len <= 0 || pin_len > 8) {
        fprintf(stderr, "pin_length must be between 1 and 8\n");
        return 1;
    }

    // Prepare target hash
    const char *target = argv[2];
    char target_hash[65];

    sha256_hex((const unsigned char*)target, strlen(target), target_hash);

    printf("Target: %s\n", target);
    printf("Hash:   %s\n", target_hash);

    // Compute search space size
    // Example: pin_len = 4 → 10^4 = 10000
    unsigned long long max = 1;
    for (int i = 0; i < pin_len; ++i)
        max *= 10ULL;

    // Shared "found" flag
    // volatile: forces threads to always read updated value
    // starts at 0 → not found, when one thread finds the password → becomes 1
    // all other threads will stop working
    volatile int found = 0;

    printf("Starting OpenMP crack with %d threads...\n",
           omp_get_max_threads());

    double start_time = omp_get_wtime();

    // OPENMP PARALLEL BRUTE FORCE LOOP
    #pragma omp parallel for schedule(dynamic) shared(found, target_hash)
    for (unsigned long long i = 0; i < max; i++) {

        // If another thread marked "found = 1",
        // then skip everything to save time.
        if (found)
            continue;

        // Private thread-local buffers
        char candidate[32];
        char hashhex[65];

        // Convert number → zero-padded string
        snprintf(candidate, sizeof(candidate), "%0*llu", pin_len, i);

        // Hash candidate
        sha256_hex((unsigned char*)candidate, strlen(candidate), hashhex);

        // Compare with target hash
        if (strcmp(hashhex, target_hash) == 0) {

            // Only one thread must print the result.
            #pragma omp critical
            {
                // Double-check inside the critical section
                if (!found) {
                    found = 1;
                    printf("FOUND! Candidate: %s (Thread %d)\n",
                           candidate, omp_get_thread_num());
                }
            }
        }
    }

    // Timing + Completion
    double end_time = omp_get_wtime();

    if (!found)
        printf("Not found in keyspace.\n");

    printf("Time taken: %.4f s\n", end_time - start_time);

    return 0;
}