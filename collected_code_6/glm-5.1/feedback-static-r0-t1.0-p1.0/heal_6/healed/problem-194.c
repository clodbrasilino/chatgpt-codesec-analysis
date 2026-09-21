#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>

unsigned long long octal_to_decimal(const char *octal_str, size_t max_len) {
    if (octal_str == NULL) {
        return 0;
    }

    unsigned long long decimal = 0;
    size_t i = 0;

    while (i < max_len && isspace((unsigned char)octal_str[i])) {
        i++;
    }

    if (i == max_len || octal_str[i] == '\0') {
        return 0;
    }

    while (i < max_len && octal_str[i] != '\0') {
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

int main(int argc, char * const * argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <octal_number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t len = strnlen(argv[1], 23);
    if (len > 22) {
        return EXIT_FAILURE;
    }

    unsigned long long result = octal_to_decimal(argv[1], len);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}