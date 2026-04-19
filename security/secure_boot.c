#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "../platform/memory_map.h"

#define FW_SIZE 1024

uint8_t firmware[FW_SIZE];
uint8_t signature[64];

extern void compute_sha256(uint8_t *data, uint32_t size, uint8_t *hash);
extern bool verify_signature(uint8_t *hash, uint8_t *signature);

printf("Primary App at: 0x%X\n", APP_PRIMARY_START);

bool secure_boot_verify() {
    uint8_t hash[32];

    printf("[BOOT] Starting Secure Boot Verification...\n");

    compute_sha256(firmware, FW_SIZE, hash);

    if (!verify_signature(hash, signature)) {
        printf("[BOOT] Firmware verification FAILED!\n");
        return false;
    }

    printf("[BOOT] Firmware verification SUCCESS!\n");
    return true;
}