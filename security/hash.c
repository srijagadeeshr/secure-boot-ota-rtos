#include <stdint.h>
#include <stdio.h>

void compute_sha256(uint8_t *data, uint32_t size, uint8_t *output_hash) {
    printf("[SECURITY] Computing SHA256 hash...\n");

    // Mock hash generation (for demo)
    for (int i = 0; i < 32; i++) {
        output_hash[i] = (uint8_t)(i + size % 255);
    }
}