#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool validate_decimal(const char *input) {
    if (input == NULL) {
        return false;
    }

    size_t len = strlen(input);
    if (len == 0) {
        return false;
    }

    size_t start = 0;
    if (input[0] == '+' || input[0] == '-') {
        if (len == 1) {
            return false;
        }
        start = 1;
    }

    char *dot_pos = strchr(input + start, '.');
    if (dot_pos == NULL) {
        return false;
    }

    if (dot_pos == input + start) {
        return false;
    }

    size_t integer_len = dot_pos - (input + start);
    for (size_t i = start; i < start + integer_len; i++) {
        if (!isdigit((unsigned char)input[i])) {
            return false;
        }
    }

    size_t fractional_len = (input + len) - (dot_pos + 1);
    if (fractional_len != 2) {
        return false;
    }

    for (size_t i = 1; i <= 2; i++) {
        if (!isdigit((unsigned char)dot_pos[i])) {
            return false;
        }
    }

    return true;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <decimal_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (validate_decimal(argv[1])) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }

    return EXIT_SUCCESS;
}