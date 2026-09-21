#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

int is_hex_even(const char *hex_str, size_t len) {
    if (hex_str == NULL || len == 0) {
        return -1;
    }

    size_t str_len = 0;
    while (str_len < len && hex_str[str_len] != '\0') {
        str_len++;
    }
    
    if (str_len == 0) {
        return -1;
    }

    size_t start = 0;
    if (str_len > 1 && hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X')) {
        if (str_len == 2) {
            return -1;
        }
        start = 2;
    }

    for (size_t i = start; i < str_len; i++) {
        if (!isxdigit((unsigned char)hex_str[i])) {
            return -1;
        }
    }

    char last_char = (char)tolower((unsigned char)hex_str[str_len - 1]);

    if (last_char == '0' || last_char == '2' || last_char == '4' || last_char == '6' || last_char == '8' || last_char == 'a' || last_char == 'c' || last_char == 'e') {
        return 1;
    }

    return 0;
}

int main(int argc, char * const * argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <hex_number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t argv1_len = 0;
    while (argv[1][argv1_len] != '\0') {
        argv1_len++;
    }
    size_t max_len = argv1_len + 1;

    int result = is_hex_even(argv[1], max_len);
    if (result == -1) {
        fprintf(stderr, "Invalid hexadecimal input\n");
        return EXIT_FAILURE;
    }

    if (result == 1) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }

    return EXIT_SUCCESS;
}