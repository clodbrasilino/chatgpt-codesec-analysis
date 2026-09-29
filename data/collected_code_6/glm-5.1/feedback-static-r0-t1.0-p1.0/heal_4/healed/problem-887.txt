#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int is_odd(int num) {
    return num & 1;
}

int main(int argc, char * const * const argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid input: not an integer\n");
        return EXIT_FAILURE;
    }

    if (val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Invalid input: out of integer range\n");
        return EXIT_FAILURE;
    }

    int num = (int)val;

    if (is_odd(num)) {
        printf("%d is odd\n", num);
    } else {
        printf("%d is even\n", num);
    }

    return EXIT_SUCCESS;
}