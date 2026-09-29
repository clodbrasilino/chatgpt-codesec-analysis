#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_leading_zeroes(const char *input, char *output, size_t max_len);

int remove_leading_zeroes(const char *input, char *output, size_t max_len) {
    if (input == NULL || output == NULL || max_len == 0) {
        return -1;
    }

    size_t i = 0;
    size_t j = 0;

    while (input[i] != '\0') {
        int is_zero = 0;
        
        while (input[i] == '0') {
            is_zero = 1;
            i++;
        }

        if (input[i] == '.' || input[i] == '\0') {
            if (is_zero) {
                if (j >= max_len - 1) {
                    return -1;
                }
                output[j++] = '0';
            }
        }

        while (input[i] != '.' && input[i] != '\0') {
            if (j >= max_len - 1) {
                return -1;
            }
            output[j++] = input[i++];
        }

        if (input[i] == '.') {
            if (j >= max_len - 1) {
                return -1;
            }
            output[j++] = input[i++];
        }
    }

    output[j] = '\0';
    return 0;
}

int main(void) {
    const char *test_ips[] = {
        "0192.0168.001.001",
        "000.000.000.000",
        "10.0.0.1",
        "0010.0000.0000.0000",
        NULL
    };

    size_t idx = 0;

    while (test_ips[idx] != NULL) {
        size_t required_len = strlen(test_ips[idx]) + 1;
        char *buffer = (char *)malloc(required_len);
        
        if (buffer != NULL) {
            if (remove_leading_zeroes(test_ips[idx], buffer, required_len) == 0) {
                printf("%s\n", buffer);
            } else {
                fprintf(stderr, "Error processing IP address\n");
            }
            free(buffer);
        } else {
            fprintf(stderr, "Memory allocation error\n");
        }
        idx++;
    }

    return 0;
}