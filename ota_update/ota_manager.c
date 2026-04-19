#include <stdio.h>

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

ota_state_t ota_state = OTA_IDLE;
extern bool secure_boot_verify();

void rollback_to_previous() {
    printf("[OTA] Rolling back to previous firmware...\n");

    // Simulate switching back to primary partition
    printf("[OTA] Booting from PRIMARY partition\n");
}

void ota_process() {
    switch (ota_state) {

        case OTA_IDLE:
            printf("[OTA] Idle state\n");
            break;

        case OTA_DOWNLOADING:
            printf("[OTA] Downloading firmware...\n");
            ota_state = OTA_VERIFYING;
            break;

        case OTA_VERIFYING:
			printf("[OTA] Verifying firmware...\n");

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
			printf("[OTA] Switching to SECONDARY partition\n");
            break;

        case OTA_FAILED:
            printf("[OTA] Update failed!\n");
			rollback_to_previous();
            break;
    }
}