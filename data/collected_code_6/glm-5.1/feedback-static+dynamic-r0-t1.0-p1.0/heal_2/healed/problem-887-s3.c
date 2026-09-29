#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int is_odd(int num) {
    return num & 1;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[ !0 ], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid input: not a valid integer\n");
        return EXIT_FAILURE;
    }

    if (val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Invalid input: integer out of range\n");
        return EXIT_FAILURE;
    }

    int num = (int)val;

    printf("%s\n", is_odd(num) ? "True" : "False");

    return EXIT_SUCCESS;
}