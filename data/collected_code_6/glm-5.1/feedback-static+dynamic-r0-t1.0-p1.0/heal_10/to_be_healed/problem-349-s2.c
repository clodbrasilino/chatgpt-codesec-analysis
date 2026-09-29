#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 1024

bool is_binary_string(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return false;
    }

    for (size_t i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return false;
        }
    }

    return true;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    size_t input_len = strnlen(argv[1], MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        fprintf(stderr, "Error: Input string exceeds maximum allowed length\n");
        return 1;
    }

    char *buffer = malloc(MAX_INPUT_LEN);
    if (buffer == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, argv[1], input_len + 1);

    if (is_binary_string(buffer, input_len)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    free(buffer);
    return 0;
}