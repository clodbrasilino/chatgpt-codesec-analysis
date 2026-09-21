#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>

unsigned long long octal_to_decimal(const char *octal_str, size_t len) {
    if (octal_str == NULL) {
        return 0;
    }

    unsigned long long decimal = 0;
    size_t i = 0;

    while (i < len && isspace((unsigned char)octal_str[i])) {
        i++;
    }

    if (i == len) {
        return 0;
    }

    while (i < len) {
        char c = octal_str[i];
        if (c < '0' || c > '7') {
            return 0;
        }
        if (decimal > (ULLONG_MAX - (c - '0')) / 8) {
            return 0;
        }
        decimal = decimal * 8 + (c - '0');
        i++;
    }

    return decimal;
}

int main(int argc, char const * const * const argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <octal_number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(argv[1]);

    unsigned long long result = octal_to_decimal(argv[1], len);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}