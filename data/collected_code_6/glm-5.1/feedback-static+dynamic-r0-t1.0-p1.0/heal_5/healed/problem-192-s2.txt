#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int check_string(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }

    int has_letter = 0;
    int has_number = 0;
    size_t len = strnlen(str, max_len);

    for (size_t i = 0; i < len; i++) {
        if (isalpha((unsigned char)str[i])) {
            has_letter = 1;
        } else if (isdigit((unsigned char)str[i])) {
            has_number = 1;
        }

        if (has_letter && has_number) {
            return 1;
        }
    }

    return 0;
}

int main(int argc, char * const *argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t max_len = 4096;
    size_t arg_len = strnlen(argv[1], max_len);

    if (arg_len >= max_len) {
        fprintf(stderr, "Error: Input string exceeds maximum allowed length.\n");
        return EXIT_FAILURE;
    }

    int result = check_string(argv[1], max_len);

    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return EXIT_SUCCESS;
}