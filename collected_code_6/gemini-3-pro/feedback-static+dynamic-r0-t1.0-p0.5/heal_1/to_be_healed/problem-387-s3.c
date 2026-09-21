#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_hex_even(const char *hex_str) {
    if (hex_str == NULL || *hex_str == '\0') {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
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