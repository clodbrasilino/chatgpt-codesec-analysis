#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_leading_zeroes(const char *ip, char *result, size_t result_size) {
    if (ip == NULL || result == NULL || result_size == 0) {
        return;
    }

    const char *ptr = ip;
    char buffer[4] = {0};
    int buff_idx = 0;
    size_t result_idx = 0;

    while (*ptr != '\0') {
        if (*ptr == '.') {
            if (buff_idx == 0) {
                if (result_idx < result_size - 1) {
                    result[result_idx++] = '0';
                }
            } else {
                for (int i = 0; i < buff_idx; i++) {
                    if (result_idx < result_size - 1) {
                        result[result_idx++] = buffer[i];
                    }
                }
            }
            if (result_idx < result_size - 1) {
                result[result_idx++] = '.';
            }
            buff_idx = 0;
        } else if (*ptr >= '0' && *ptr <= '9') {
            if (buff_idx == 0 && *ptr == '0') {
                const char *next = ptr + 1;
                if (*next >= '0' && *next <= '9') {
                    ptr++;
                    continue;
                }
            }
            if (buff_idx < 3) {
                buffer[buff_idx++] = *ptr;
            }
        }
        ptr++;
    }

    if (buff_idx == 0) {
        if (result_idx < result_size - 1) {
            result[result_idx++] = '0';
        }
    } else {
        for (int i = 0; i < buff_idx; i++) {
            if (result_idx < result_size - 1) {
                result[result_idx++] = buffer[i];
            }
        }
    }

    result[result_idx] = '\0';
}

int main(void) {
    const char *test_ips[] = {
        "192.168.001.001",
        "010.000.020.030",
        "0.00.000.0",
        "172.016.254.001",
        NULL
    };

    for (size_t i = 0; test_ips[i] != NULL; i++) {
        char result[16] = {0};
        remove_leading_zeroes(test_ips[i], result, sizeof(result));
        printf("%s -> %s\n", test_ips[i], result);
    }

    return 0;
}