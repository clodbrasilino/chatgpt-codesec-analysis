#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

unsigned long perrin(int n) {
    if (n == 0) {
        return 3;
    }
    if (n == 1) {
        return 0;
    }
    if (n == 2) {
        return 2;
    }

    unsigned long p0 = 3;
    unsigned long p1 = 0;
    unsigned long p2 = 2;
    unsigned long pn = 2;

    for (int i = 3; i <= n; i++) {
        pn = p0 + p1;
        p0 = p1;
        p1 = p2;
        p2 = pn;
    }

    return pn;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || errno != 0) {
        return EXIT_FAILURE;
    }

    if (val < 0 || val > 35) {
        return EXIT_FAILURE;
    }

    int n = (int)val;
    unsigned long result = perrin(n);
    printf("%lu\n", result);

    return EXIT_SUCCESS;
}