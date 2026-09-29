#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int count_flips(const char *str, size_t maxlen) {
    size_t len = strnlen(str, maxlen);
    if (len == 0) {
        return 0;
    }

    int flip1 = 0;
    int flip2 = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1') {
            exit(EXIT_FAILURE);
        }

        if (i % 2 == 0) {
            if (str[i] != '0') flip1++;
            if (str[i] != '1') flip2++;
        } else {
            if (str[i] != '1') flip1++;
            if (str[i] != '0') flip2++;
        }
    }

    return min(flip1, flip2);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t maxlen = 4096;
    size_t len = strnlen(argv[1], maxlen);
    if (len == maxlen) {
        fprintf(stderr, "Error: Input string exceeds maximum allowed length\n");
        return EXIT_FAILURE;
    }

    char *buffer = malloc(len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(buffer, argv[1], len + 1);

    int result = count_flips(buffer, maxlen);
    printf("%d\n", result);

    free(buffer);

    return EXIT_SUCCESS;
}