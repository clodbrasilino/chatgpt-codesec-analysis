#include <stdio.h>
#include <string.h>
#include <ctype.h>

int remove_leading_zeroes(const char *ip, char *result, size_t result_size);

int remove_leading_zeroes(const char *ip, char *result, size_t result_size) {
    size_t dest_idx = 0;
    const char *src = ip;

    if (ip == NULL || result == NULL || result_size == 0) {
        return -1;
    }

    while (*src != '\0') {
        if (isdigit((unsigned char)*src)) {
            while (*src == '0' && isdigit((unsigned char)*(src + 1))) {
                src++;
            }
            while (isdigit((unsigned char)*src)) {
                if (dest_idx < result_size - 1) {
                    result[dest_idx++] = *src;
                } else {
                    return -1;
                }
                src++;
            }
        } else {
            if (dest_idx < result_size - 1) {
                result[dest_idx++] = *src;
            } else {
                return -1;
            }
            src++;
        }
    }
    
    result[dest_idx] = '\0';
    return 0;
}

int main(void) {
    const char *test_ips[] = {
        "192.168.001.01",
        "000.000.000.000",
        "010.000.055.099",
        "2001:0db8:0000:0000:0000:ff00:0042:8329"
    };
    size_t num_ips = sizeof(test_ips) / sizeof(test_ips[0]);
    char result[128];

    for (size_t i = 0; i < num_ips; i++) {
        if (test_ips[i] != NULL) {
            if (remove_leading_zeroes(test_ips[i], result, sizeof(result)) == 0) {
                printf("%s\n", result);
            }
        }
    }

    return 0;
}