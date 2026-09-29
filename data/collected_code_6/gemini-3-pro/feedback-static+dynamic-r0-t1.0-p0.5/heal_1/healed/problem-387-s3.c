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

    char last_char = 0;
    while (hex_str[i] != '\0') {
        if (!isxdigit((unsigned char)hex_str[i])) {
            return -1;
        }
        last_char = (char)tolower((unsigned char)hex_str[i]);
        i++;
    }

    int last_digit;
    if (isdigit((unsigned char)last_char)) {
        last_digit = last_char - '0';
    } else {
        last_digit = last_char - 'a' + 10;
    }

    return (last_digit % 2 == 0) ? 1 : 0;
}

int main(int argc, const char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <hexadecimal_number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = is_hex_even(argv[1]);

    if (result == -1) {
        fprintf(stderr, "Error: Invalid hexadecimal input.\n");
        return EXIT_FAILURE;
    }

    if (result == 1) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }

    return EXIT_SUCCESS;
}