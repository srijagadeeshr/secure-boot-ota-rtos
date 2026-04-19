#include <stdio.h>
#include "../platform/memory_map.h"
#include "../utils/log.h"

int retry_count = 0;
#define MAX_RETRIES 3
uint32_t current_version = 2;
uint32_t new_version = 1;

typedef enum {
    PARTITION_PRIMARY,
    PARTITION_SECONDARY
} partition_t;

// In real system, this should be stored in non-volatile memory (Flash / EEPROM)
partition_t active_partition = PARTITION_PRIMARY;

typedef enum {
    FW_VALID,
    FW_INVALID
} firmware_status_t;

firmware_status_t new_firmware_status = FW_INVALID;

typedef enum {
    OTA_IDLE,
    OTA_DOWNLOADING,
    OTA_VERIFYING,
    OTA_SUCCESS,
    OTA_FAILED
} ota_state_t;

typedef struct {
    uint32_t version;
    uint32_t size;
    uint8_t signature[64];
} firmware_metadata_t;

firmware_metadata_t new_fw;
// NOTE:
// In real embedded systems, OTA state, active partition,
// and firmware confirmation flags must be stored in non-volatile memory
// (Flash/EEPROM) to survive power cycles.
ota_state_t ota_state = OTA_IDLE;
extern bool secure_boot_verify();

void rollback_to_previous() {
   // printf("[OTA] Rolling back to previous firmware...\n");
	//printf("[OTA] Booting from address: 0x%X\n", APP_PRIMARY_START);
	LOG_OTA([OTA] Booting from address: 0x%X\n,APP_PRIMARY_START)
	}

void ota_process() {
	//IDLE → DOWNLOADING → VERIFYING (secure boot)→ SUCCESS(switch partition)/FAILED( retry → rollback)
    switch (ota_state) {

        case OTA_IDLE:
            printf("[OTA] Idle state\n");
			ota_state = OTA_DOWNLOADING;
            break;

        case OTA_DOWNLOADING:
            printf("[OTA] Downloading firmware...\n");
			// Simulate download completion
			int download_complete = 1;

			if (download_complete) {
				ota_state = OTA_VERIFYING;
			}
            break;

        case OTA_VERIFYING:
			printf("[OTA] Validating firmware before activation...\n");

			if (new_version <= current_version) {
				printf("[SECURITY] Rejecting downgrade attack\n");
				ota_state = OTA_FAILED;
			}
			if (secure_boot_verify()) {
				new_firmware_status = FW_VALID;
				ota_state = OTA_SUCCESS;
			} else {
				new_firmware_status = FW_INVALID;
				ota_state = OTA_FAILED;
			}
			break;


        case OTA_SUCCESS:
            printf("[OTA] Update successful!\n");
			active_partition = PARTITION_SECONDARY;
			printf("[OTA] Switching to SECONDARY partition\n");
            break;

        case OTA_FAILED:
			retry_count++;

			if (retry_count < MAX_RETRIES) {
				printf("[OTA] Retry OTA...\n");
				ota_state = OTA_DOWNLOADING;
			} else {
				rollback_to_previous();
			}
			break;
    }
}