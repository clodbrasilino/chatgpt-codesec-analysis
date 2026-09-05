#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int binary_to_decimal(const char *binary_str) {
    if (binary_str == NULL) {
        return -1;
    }

    size_t len = strlen(binary_str);
    if (len == 0 || len > 31) {
        return -1;
    }

    int decimal = 0;
    for (size_t i = 0; i < len; i++) {
        if (binary_str[i] != '0' && binary_str[i] != '1') {
            return -1;
        }
        decimal = decimal * 2 + (binary_str[i] - '0');
    }

    return decimal;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = binary_to_decimal(argv[1]);
    if (result < 0) {
        fprintf(stderr, "Invalid binary string provided\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}