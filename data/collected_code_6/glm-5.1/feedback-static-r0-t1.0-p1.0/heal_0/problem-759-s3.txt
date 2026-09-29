#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool check_decimal(const char *input) {
    if (input == NULL) {
        return false;
    }

    size_t len = strlen(input);
    if (len == 0) {
        return false;
    }

    size_t start = 0;
    if (input[0] == '-') {
        start = 1;
        if (len == 1) {
            return false;
        }
    }

    for (size_t i = start; i < len; i++) {
        if (!isdigit((unsigned char)input[i]) && input[i] != '.') {
            return false;
        }
    }

    char *dot_ptr = strchr(input, '.');
    if (dot_ptr == NULL) {
        return false;
    }

    if (strchr(dot_ptr + 1, '.') != NULL) {
        return false;
    }

    size_t integer_digits = dot_ptr - (input + start);
    if (integer_digits == 0) {
        return false;
    }

    size_t fractional_digits = len - (dot_ptr - input) - 1;
    if (fractional_digits != 2) {
        return false;
    }

    return true;
}

int main(void) {
    const char *test_cases[] = {
        "123.45",
        "-12.34",
        "0.00",
        ".45",
        "123.4",
        "123.456",
        "abc.de",
        "12.3.4",
        "",
        "-.45",
        "123.",
        NULL
    };

    for (int i = 0; i < (int)(sizeof(test_cases) / sizeof(test_cases[0])); i++) {
        bool result = check_decimal(test_cases[i]);
        if (result) {
            printf("Valid: %s\n", test_cases[i] ? test_cases[i] : "NULL");
        } else {
            printf("Invalid: %s\n", test_cases[i] ? test_cases[i] : "NULL");
        }
    }

    return 0;
}