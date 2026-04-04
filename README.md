# secure-boot-ota-rtos

Secure Bootloader with OTA Update using RTOS and Cryptography

\# Project Status: In Progress



## Overview

This project implements a secure bootloader supporting OTA firmware updates with cryptographic verification and rollback protection.



## Key Features

* Secure boot using signature verification (RSA/SHA)
* OTA firmware update with rollback support
* RTOS-based task handling
* Flash memory partitioning
* Python-based firmware signing tool



## Boot Flow

1. System Power ON
2. Bootloader initializes memory and peripherals
3. Firmware signature verification
4. Jump to application if valid
5. OTA update if new firmware available
6. Rollback if update fails



## Folder Structure

* bootloader/ ? startup, linker, verification
* ota\_update/ ? update logic
* crypto/ ? cryptographic functions
* rtos/ ? task scheduling
* drivers/ ? hardware interfaces
* tools/ ? signing scripts

