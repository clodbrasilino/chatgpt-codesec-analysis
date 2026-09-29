#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_hex_even(const char *hex_str);

int is_hex_even(const char *hex_str) {
    size_t len;
    size_t start = 0;
    char last_char;
    size_t i;

    if (hex_str == NULL) {
        return -1;
    }

    len = strlen(hex_str);

    if (len >= 2 && hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X')) {
        start = 2;
    }

    if (start == len) {
        return -1;
    }

    for (i = start; i < len; i++) {
        if (!isxdigit((unsigned char)hex_str[i])) {
            return -1;
        }
    }

    last_char = (char)tolower((unsigned char)hex_str[len - 1]);

    switch (last_char) {
        case '0':
        case '2':
        case '4':
        case '6':
        case '8':
        case 'a':
        case 'c':
        case 'e':
            return 1;
        case '1':
        case '3':
        case '5':
        case '7':
        case '9':
        case 'b':
        case 'd':
        case 'f':
            return 0;
        default:
            return -1;
    }
}

int main(void) {
    const char *test_cases[] = {
        "0x1A4",
        "0x1A5",
        "1A4",
        "1A5",
        "0x",
        "0XG",
        "",
        NULL
    };
    
    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    size_t i;

    for (i = 0; i < num_cases; i++) {
        int result = is_hex_even(test_cases[i]);
        if (result == 1) {
            printf("Even\n");
        } else if (result == 0) {
            printf("Odd\n");
        } else {
            printf("Invalid\n");
        }
    }

    return 0;
}