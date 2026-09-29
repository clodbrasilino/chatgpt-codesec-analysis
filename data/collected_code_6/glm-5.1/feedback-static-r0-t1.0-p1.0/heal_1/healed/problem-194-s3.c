#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

long long octal_to_decimal(const char *str) {
    if (str == NULL) {
        errno = EINVAL;
        return 0;
    }

    while (isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == '\0') {
        errno = EINVAL;
        return 0;
    }

    long long result = 0;

    while (*str != '\0') {
        if (*str < '0' || *str > '7') {
            errno = EINVAL;
            return 0;
        }

        int digit = *str - '0';

        if (result > (LLONG_MAX - digit) / 8) {
            errno = ERANGE;
            return LLONG_MAX;
        }

        result = result * 8 + digit;
        str++;
    }

    return result;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <octal_number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    long long decimal = octal_to_decimal(argv[1]);

    if (errno == EINVAL) {
        fprintf(stderr, "Error: Invalid octal number format.\n");
        return EXIT_FAILURE;
    }

    if (errno == ERANGE) {
        fprintf(stderr, "Error: Octal number out of range.\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", decimal);

    return EXIT_SUCCESS;
}