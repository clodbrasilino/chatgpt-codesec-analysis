#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int remove_ip_leading_zeroes(const char *src, char *dest, size_t dest_size) {
    if (src == NULL || dest == NULL || dest_size == 0) {
        return -1;
    }

    size_t j = 0;
    int at_octet_start = 1;
    size_t i;

    for (i = 0; src[i] != '\0'; ++i) {
        if (at_octet_start && src[i] == '0' && isdigit((unsigned char)src[i + 1])) {
            continue;
        }

        if (j >= dest_size - 1) {
            break;
        }

        dest[j++] = src[i];
        at_octet_start = (src[i] == '.');
    }

    dest[j] = '\0';

    if (src[i] != '\0') {
        return -1;
    }

    return 0;
}

int main(void) {
    const char *addresses[] = {
        "192.168.001.010",
        "010.000.000.001",
        "0.0.0.0",
        "255.255.255.255",
        "001.002.003.004"
    };
    size_t count = sizeof(addresses) / sizeof(addresses[0]);

    for (size_t i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buffer[16];
        
        if (remove_ip_leading_zeroes(addresses[i], buffer, sizeof(buffer)) == 0) {
            printf("%s -> %s\n", addresses[i], buffer);
        } else {
            printf("Error processing: %s\n", addresses[i]);
        }
    }

    return 0;
}