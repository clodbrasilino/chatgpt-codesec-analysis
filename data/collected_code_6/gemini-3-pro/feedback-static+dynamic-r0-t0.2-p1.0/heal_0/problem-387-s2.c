#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_hex_even(const char *hex_str) {
    if (hex_str == NULL || *hex_str == '\0') {
        return -1;
    }

    size_t len = strlen(hex_str);
    size_t start = 0;

    if (len > 2 && hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X')) {
        start = 2;
    }

    if (start == len) {
        return -1;
    }

    for (size_t i = start; i < len; i++) {
        if (!isxdigit((unsigned char)hex_str[i])) {
            return -1;
        }
    }

    char last_char = tolower((unsigned char)hex_str[len - 1]);
    int last_digit;

    if (isdigit((unsigned char)last_char)) {
        last_digit = last_char - '0';
    } else {
        last_digit = last_char - 'a' + 10;
    }

    return (last_digit % 2 == 0) ? 1 : 0;
}

int main(void) {
    const char *test_cases[] = {
        "0x1A",
        "1B",
        "0x1234",
        "0x1235",
        "invalid",
        "",
        NULL
    };

    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_cases; i++) {
        int result = is_hex_even(test_cases[i]);
        if (result == 1) {
            printf("Even\n");
        } else if (result == 0) {
            printf("Odd\n");
        } else {
            printf("Invalid\n");
        }
    }

    return EXIT_SUCCESS;
}