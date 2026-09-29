#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_even_hex(const char *hex_str) {
    if (hex_str == NULL || *hex_str == '\0') {
        return -1;
    }

    const char *p = hex_str;
    while (*p) {
        if (!isxdigit((unsigned char)*p)) {
            return -1;
        }
        p++;
    }

    size_t len = strlen(hex_str);
    char last_char = hex_str[len - 1];

    int last_digit;
    if (last_char >= '0' && last_char <= '9') {
        last_digit = last_char - '0';
    } else if (last_char >= 'a' && last_char <= 'f') {
        last_digit = last_char - 'a' + 10;
    } else if (last_char >= 'A' && last_char <= 'F') {
        last_digit = last_char - 'A' + 10;
    } else {
        return -1;
    }

    return (last_digit % 2 == 0) ? 1 : 0;
}

int main(void) {
    const char *test_cases[] = {
        "1A",
        "1B",
        "FF",
        "FE",
        "0",
        "1",
        "ABCDEF",
        "ABCDEE",
        "1234567890",
        "1234567891",
        "invalid",
        "",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        int result = is_even_hex(test_cases[i]);
        if (result == -1) {
            printf("%s: invalid input\n", test_cases[i]);
        } else if (result == 1) {
            printf("%s: even\n", test_cases[i]);
        } else {
            printf("%s: odd\n", test_cases[i]);
        }
    }

    return 0;
}