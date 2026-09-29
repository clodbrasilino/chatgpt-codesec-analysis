#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int is_hex_even(const char *hex_str) {
    if (hex_str == NULL || *hex_str == '\0') {
        return -1;
    }

    size_t i = 0;
    if (hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X')) {
        i = 2;
    }

    if (hex_str[i] == '\0') {
        return -1;
    }

    int last_digit = -1;

    while (hex_str[i] != '\0') {
        unsigned char c = (unsigned char)hex_str[i];
        if (!isxdigit(c)) {
            return -1;
        }

        c = tolower(c);
        if (isdigit(c)) {
            last_digit = c - '0';
        } else {
            last_digit = c - 'a' + 10;
        }
        i++;
    }

    if (last_digit == -1) {
        return -1;
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