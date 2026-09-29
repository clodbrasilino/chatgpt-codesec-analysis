#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int remove_ip_leading_zeroes(const char *src, char *dest, size_t dest_size) {
    if (src == NULL || dest == NULL || dest_size == 0) {
        return -1;
    }

    size_t src_len = strnlen(src, 256);
    if (src_len == 0) {
        dest[0] = '\0';
        return 0;
    }

    size_t j = 0;
    int truncated = 0;
    int octet_start = 1;

    for (size_t i = 0; i < src_len; ++i) {
        int skip = 0;
        if (src[i] == '.') {
            octet_start = 1;
        } else {
            if (src[i] == '0' && octet_start && (i + 1 < src_len) && isdigit((unsigned char)src[i + 1])) {
                skip = 1;
            } else {
                octet_start = 0;
            }
        }

        if (!skip) {
            if (j >= dest_size - 1) {
                truncated = 1;
                break;
            }
            dest[j++] = src[i];
        }
    }

    dest[j] = '\0';
    return truncated ? -1 : 0;
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
        size_t len = strnlen(addresses[i], 256);
        char *buffer = malloc(len + 1);
        if (buffer == NULL) {
            printf("Error processing: %s\n", addresses[i]);
            continue;
        }
        if (remove_ip_leading_zeroes(addresses[i], buffer, len + 1) == 0) {
            printf("%s -> %s\n", addresses[i], buffer);
        } else {
            printf("Error processing: %s\n", addresses[i]);
        }
        free(buffer);
    }

    return 0;
}