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

    if (last_char >= '0' && last_char <= '9') {
        return (last_char - '0') % 2 == 0;
    } else {
        last_char = tolower((unsigned char)last_char);
        int value = last_char - 'a' + 10;
        return value % 2 == 0;
    }
}

int main(void) {
    const char *test_cases[] = {
        "1A",
        "1B",
        "2",
        "3",
        "FF",
        "FE",
        "10",
        "11",
        "0",
        "1",
        "A",
        "B",
        "invalid",
        "",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        int result = is_even_hex(test_cases[i]);
        if (result == -1) {
            printf("%s: Invalid hexadecimal number\n", test_cases[i]);
        } else if (result == 1) {
            printf("%s: Even\n", test_cases[i]);
        } else {
            printf("%s: Odd\n", test_cases[i]);
        }
    }

    return 0;
}