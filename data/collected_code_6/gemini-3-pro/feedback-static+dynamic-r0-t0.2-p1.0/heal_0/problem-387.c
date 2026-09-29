#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool is_hex_even(const char *hex_str) {
    if (hex_str == NULL || *hex_str == '\0') {
        return false;
    }

    size_t len = strlen(hex_str);
    size_t start = 0;

    if (len > 2 && hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X')) {
        start = 2;
    }

    if (start == len) {
        return false;
    }

    for (size_t i = start; i < len; i++) {
        if (!isxdigit((unsigned char)hex_str[i])) {
            return false;
        }
    }

    char last_char = tolower((unsigned char)hex_str[len - 1]);
    
    if (last_char == '0' || last_char == '2' || last_char == '4' || 
        last_char == '6' || last_char == '8' || last_char == 'a' || 
        last_char == 'c' || last_char == 'e') {
        return true;
    }

    return false;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <hexadecimal_number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (is_hex_even(argv[1])) {
        printf("Even\n");
    } else {
        printf("Odd or Invalid\n");
    }

    return EXIT_SUCCESS;
}