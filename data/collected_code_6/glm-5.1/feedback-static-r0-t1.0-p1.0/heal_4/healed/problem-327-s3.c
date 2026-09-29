#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int is_isosceles(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if ((long)a + (long)b <= c || (long)a + (long)c <= b || (long)b + (long)c <= a) {
        return 0;
    }
    if (a == b || b == c || a == c) {
        return 1;
    }
    return 0;
}

int main(int argc, char * const * const argv) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr_a;
    long va = strtol(argv[1], &endptr_a, 10);
    if (errno != 0 || *endptr_a != '\0' || va > INT_MAX) {
        return EXIT_FAILURE;
    }

    char *endptr_b;
    long vb = strtol(argv[2], &endptr_b, 10);
    if (errno != 0 || *endptr_b != '\0' || vb > INT_MAX) {
        return EXIT_FAILURE;
    }

    char *endptr_c;
    long vc = strtol(argv[3], &endptr_c, 10);
    if (errno != 0 || *endptr_c != '\0' || vc > INT_MAX) {
        return EXIT_FAILURE;
    }

    if (va <= 0 || vb <= 0 || vc <= 0) {
        return EXIT_FAILURE;
    }

    int a = (int)va;
    int b = (int)vb;
    int c = (int)vc;

    if (is_isosceles(a, b, c)) {
        printf("Isosceles\n");
    } else {
        printf("Not Isosceles\n");
    }

    return EXIT_SUCCESS;
}