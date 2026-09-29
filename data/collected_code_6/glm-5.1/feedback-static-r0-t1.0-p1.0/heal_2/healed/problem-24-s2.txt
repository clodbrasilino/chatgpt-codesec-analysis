#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

int binary_to_decimal(const char *binary_str, long *result) {
    if (binary_str == NULL || result == NULL) {
        return -1;
    }

    size_t max_len = sizeof(long) * CHAR_BIT;
    size_t len = 0;
    const char *ptr = binary_str;
    while (*ptr != '\0') {
        len++;
        if (len > max_len) {
            return -1;
        }
        ptr++;
    }

    if (len == 0) {
        return -1;
    }

    for (size_t i = 0; i < len; i++) {
        if (binary_str[i] != '0' && binary_str[i] != '1') {
            return -1;
        }
    }

    errno = 0;
    char *endptr;
    long dec_val = strtol(binary_str, &endptr, 2);

    if (errno == ERANGE || *endptr != '\0') {
        return -1;
    }

    *result = dec_val;
    return 0;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    long decimal_value;
    if (binary_to_decimal(argv[1], &decimal_value) != 0) {
        fprintf(stderr, "Invalid binary input or out of range.\n");
        return EXIT_FAILURE;
    }

    printf("%ld\n", decimal_value);
    return EXIT_SUCCESS;
}