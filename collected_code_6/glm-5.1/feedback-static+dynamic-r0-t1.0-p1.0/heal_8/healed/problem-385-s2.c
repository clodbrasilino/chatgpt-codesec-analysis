#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long perrin(int n) {
    if (n == 0) return 3;
    if (n == 1) return 0;
    if (n == 2) return 2;
    unsigned long p0 = 3, p1 = 0, p2 = 2;
    for (int i = 3; i <= n; i++) {
        unsigned long next = p0 + p1;
        p0 = p1;
        p1 = p2;
        p2 = next;
    }
    return p2;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || val < 0 || errno == ERANGE || val > INT_MAX) {
        fprintf(stderr, "Error: n must be a non-negative integer within valid range\n");
        return EXIT_FAILURE;
    }

    unsigned long result = perrin((int)val);
    printf("%lu\n", result);

    return EXIT_SUCCESS;
}