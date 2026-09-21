#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int jumpsRequired(int d, int l) {
    if (d == 0) {
        return 0;
    }
    if (d < 0) {
        d = -d;
    }
    if (l <= 0) {
        return -1;
    }
    if (d % l == 0) {
        return d / l;
    }
    if (d < l) {
        return 2;
    }
    return (d / l) + 1;
}

int main(int argc, char *argv[]) {
    int d, l;
    char *endptr;
    long val;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <distance> <jump_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Invalid distance value\n");
        return EXIT_FAILURE;
    }
    d = (int)val;

    errno = 0;
    val = strtol(argv[2], &endptr, 10);
    if (errno != 0 || endptr == argv[2] || *endptr != '\0' || val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Invalid jump length value\n");
        return EXIT_FAILURE;
    }
    l = (int)val;

    int result = jumpsRequired(d, l);
    if (result == -1) {
        printf("Invalid jump length\n");
    } else {
        printf("%d\n", result);
    }
    return EXIT_SUCCESS;
}