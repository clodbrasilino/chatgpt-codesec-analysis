#include <stdio.h>
#include <string.h>
#include <ctype.h>

int remove_ip_leading_zeroes(const char *src, char *dest, size_t dest_size) {
    if (src == NULL || dest == NULL || dest_size == 0) {
        return -1;
    }

    size_t src_len = strlen(src);
    if (src_len == 0) {
        dest[0] = '\0';
        return 0;
    }

    size_t j = 0;
    for (size_t i = 0; i < src_len; ++i) {
        if (src[i] == '0' && isdigit((unsigned char)src[i + 1]) && (i == 0 || src[i - 1] == '.')) {
            continue;
        }
        if (j >= dest_size - 1) {
            dest[j] = '\0';
            return -1;
        }
        dest[j++] = src[i];
    }

    dest[j] = '\0';
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
    char buffer[16];
    size_t count = sizeof(addresses) / sizeof(addresses[0]);

    for (size_t i = 0; i < count; ++i) {
        if (remove_ip_leading_zeroes(addresses[i], buffer, sizeof(buffer)) == 0) {
            printf("%s -> %s\n", addresses[i], buffer);
        } else {
            printf("Error processing: %s\n", addresses[i]);
        }
    }

    return 0;
}