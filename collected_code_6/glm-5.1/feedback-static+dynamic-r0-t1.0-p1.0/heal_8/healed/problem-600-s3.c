#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

bool is_even(int num) {
    return (num & 1) == 0;
}

int main(int argc, char * const argv[static const restrict 2]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    if (argv[1][0] == '\0') {
        return EXIT_FAILURE;
    }
    size_t len = strnlen(argv[1], 12);
    if (len == 0 || len > 11) {
        return EXIT_FAILURE;
    }
    errno = 0;
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int num = (int)val;
    if (is_even(num)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    return EXIT_SUCCESS;
}