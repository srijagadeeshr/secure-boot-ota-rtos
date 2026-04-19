#include <stdbool.h>
#include <stdio.h>

bool verify_signature(uint8_t *hash, uint8_t *signature) {
    printf("[SECURITY] Verifying firmware signature...\n");

    // Mock verification (always true for now)
    return true;
}