#include <stdio.h>
#include <stdbool.h>

bool secure_boot_verify();

int main() {
    printf("System Power ON\n");

    if (!secure_boot_verify()) {
        printf("Staying in bootloader (invalid firmware)\n");
        return -1;
    }

    printf("Jumping to Application...\n");
    return 0;
}