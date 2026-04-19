## Overview

This project implements a secure bootloader with OTA firmware update capability, designed to simulate an automotive ECU firmware update system with strong security guarantees.

The system ensures that only authenticated firmware is executed, while supporting safe and reliable remote updates with rollback protection.

---

## Key Features

* Secure Boot using cryptographic signature verification (RSA/SHA256 – mock implementation)
* OTA firmware update with dual-partition strategy
* Fail-safe rollback mechanism
* RTOS-based task handling for OTA workflow
* Flash memory partitioning (Bootloader, Primary, Secondary)
* Python-based firmware signing tool (simulated)

---

## Architecture Summary

* Bootloader handles secure boot and partition selection
* OTA manager handles firmware update lifecycle
* Security module performs hash and signature verification
* Platform layer defines memory layout

---

## Boot Flow (Secure Boot)

1. System Power ON
2. Bootloader execution starts
3. Firmware image is read from flash
4. Hash (SHA256) is computed
5. Signature verification is performed
6. If valid → Jump to application
7. If invalid → Stay in bootloader / recovery mode

---

## OTA Update Flow

1. Firmware is received in chunks
2. Stored in secondary partition
3. Integrity check is performed
4. Signature verification is done
5. Firmware marked as valid
6. On next reboot → switch to new firmware

---

## Memory Layout

* Bootloader Region (Read-only)
* Primary Application (Active firmware)
* Secondary Application (OTA update region)

---

## Security Considerations

* Prevent execution of unauthorized firmware
* Protect against corrupted OTA updates
* Ensure rollback to last known good image
* Simulated cryptographic validation (extendable to HSM)

---

## Failure handling 

* Power loss during OTA
* Partial firmware write
* Invalid firmware

---

## Threat Model
* Replay attack
* Downgrade attack
* Unauthorized firmware

---

## How to Run

* Compile using GCC (optional)
* Run main.c to simulate boot + OTA flow

---

## Failure Handling

* Power loss
* Partial update
* Invalid firmware
---

## Key Design Highlights

* A/B partition OTA strategy
* Secure boot with signature verification
* Trial boot with firmware confirmation
* Rollback mechanism for reliability

---

## Limitations

- Cryptographic operations are mocked for demonstration
- No real hardware flash interaction implemented

---

## Key Design Decisions

- A/B partitioning for safe OTA updates
- Verification before activation to prevent corrupted firmware execution
- Trial boot with confirmation to avoid permanent faulty firmware
- Rollback mechanism to ensure system reliability

---

## Flow Chart 

Bootloader → Verify → Select Partition → Jump
          ↑
        OTA Update → Secondary → Verify → Confirm
		
---

## Future Enhancements

* Integration with real crypto libraries (mbedTLS)
* Hardware Security Module (HSM) support
* UDS/CAN-based OTA communication
* AUTOSAR integration
