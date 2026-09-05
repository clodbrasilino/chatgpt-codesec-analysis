#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long tetrahedral(unsigned int n) {
    if (n > 208) {
        return 0;
    }
    unsigned long a = n;
    unsigned long b = n + 1;
    unsigned long c = n + 2;
    if (a % 2 == 0) {
        a /= 2;
    } else if (b % 2 == 0) {
        b /= 2;
    } else {
        c /= 2;
    }
    if (a % 3 == 0) {
        a /= 3;
    } else if (b % 3 == 0) {
        b /= 3;
    } else {
        c /= 3;
    }
    if (a > ULONG_MAX / b) {
        return 0;
    }
    unsigned long ab = a * b;
    if (ab > ULONG_MAX / c) {
        return 0;
    }
    return ab * c;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    errno = 0;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || val > UINT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    unsigned int n = (unsigned int)val;
    unsigned long result = tetrahedral(n);
    if (result == 0 && n > 0) {
        fprintf(stderr, "Overflow\n");
        return EXIT_FAILURE;
    }
    printf("%lu\n", result);
    return EXIT_SUCCESS;
}