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

    switch (tolower((unsigned char)last_char)) {
        case '0': case '2': case '4': case '6': case '8':
        case 'a': case 'c': case 'e':
            return 1;
        case '1': case '3': case '5': case '7': case '9':
        case 'b': case 'd': case 'f':
            return 0;
        default:
            return -1;
    }
}

int main(void) {
    const char *test_cases[] = {
        "1A", "2B", "FF", "10", "0", "7", "8", "ABC", "ABD", NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        int result = is_even_hex(test_cases[i]);
        if (result == 1) {
            printf("%s is even\n", test_cases[i]);
        } else if (result == 0) {
            printf("%s is odd\n", test_cases[i]);
        } else {
            printf("%s is invalid\n", test_cases[i]);
        }
    }

    return 0;
}