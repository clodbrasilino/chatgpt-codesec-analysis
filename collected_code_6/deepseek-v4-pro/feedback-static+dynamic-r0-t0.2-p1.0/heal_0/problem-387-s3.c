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
    char last_char = tolower((unsigned char)hex_str[len - 1]);
    
    if (last_char == '0' || last_char == '2' || last_char == '4' ||
        last_char == '6' || last_char == '8' || last_char == 'a' ||
        last_char == 'c' || last_char == 'e') {
        return 1;
    }
    
    return 0;
}

int main(void) {
    const char *test_cases[] = {
        "1A",
        "1B",
        "FF",
        "FE",
        "1234",
        "1235",
        "0",
        "1",
        "ABCDEF",
        "ABCDEE",
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