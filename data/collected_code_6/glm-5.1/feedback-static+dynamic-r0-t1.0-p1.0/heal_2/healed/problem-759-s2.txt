#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool validate_decimal(const char *str, size_t max_len) {
    if (str == NULL) {
        return false;
    }

    size_t len = strnlen(str, max_len);
    if (len == 0 || len == max_len) {
        return false;
    }

    size_t i = 0;

    if (str[0] == '-' || str[0] == '+') {
        i = 1;
        if (i == len) {
            return false;
        }
    }

    bool has_digit = false;
    bool has_dot = false;
    size_t precision = 0;

    for (; i < len; i++) {
        if (str[i] == '.') {
            if (has_dot) {
                return false;
            }
            has_dot = true;
        } else if (isdigit((unsigned char)str[i])) {
            has_digit = true;
            if (has_dot) {
                precision++;
                if (precision > 2) {
                    return false;
                }
            }
        } else {
            return false;
        }
    }

    if (!has_digit) {
        return false;
    }

    if (has_dot && precision == 0) {
        return false;
    }

    return true;
}

int main(int argc, char const * const * argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <decimal_number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (validate_decimal(argv[1], 256)) {
        printf("Valid\n");
        return EXIT_SUCCESS;
    } else {
        printf("Invalid\n");
        return EXIT_FAILURE;
    }
}