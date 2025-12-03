// brute_serial.c
// Serial brute-force SHA-256 simulation over numeric PINs.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

void sha256_hex(const unsigned char *input, size_t len, char outhex[65]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(input, len, hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        sprintf(outhex + (i * 2), "%02x", hash[i]);
    outhex[64] = 0;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <pin_length> <target_password>\n", argv[0]);
        printf("Example: %s 4 0420\n", argv[0]);
        return 1;
    }

    int pin_len = atoi(argv[1]);
    if (pin_len <= 0 || pin_len > 8) {
        fprintf(stderr, "pin_length must be between 1 and 8\n");
        return 1;
    }

    const char *target = argv[2];
    char target_hash[65];
    sha256_hex((const unsigned char*)target, strlen(target), target_hash);
    printf("Target password (synthetic): %s\n", target);
    printf("Target SHA-256: %s\n", target_hash);

    // Calculate the total keyspace (e.g., 10^pin_len)
    unsigned long long max = 1;
    for (int i = 0; i < pin_len; ++i) max *= 10ULL;

    char candidate[32];
    char hashhex[65];
    clock_t t0 = clock();

    // Main serial loop
    for (unsigned long long i = 0; i < max; ++i) {
        // Generate zero-padded candidate, e.g., "0003" for pin_len=4
        snprintf(candidate, sizeof(candidate), "%0*llu", pin_len, i);
        
        // Hash the candidate
        sha256_hex((const unsigned char*)candidate, strlen(candidate), hashhex);

        // Check for a match
        if (strcmp(hashhex, target_hash) == 0) {
            clock_t t1 = clock();
            double secs = (double)(t1 - t0) / CLOCKS_PER_SEC;
            printf("FOUND! Candidate: %s\n", candidate);
            printf("Time taken: %.3f s, Attempts: %llu\n", secs, i + 1);
            return 0; // Exit after finding
        }
    }

    clock_t t1 = clock();
    double secs = (double)(t1 - t0) / CLOCKS_PER_SEC;
    printf("Not found in keyspace. Time: %.3f s\n", secs);
    return 0;
}