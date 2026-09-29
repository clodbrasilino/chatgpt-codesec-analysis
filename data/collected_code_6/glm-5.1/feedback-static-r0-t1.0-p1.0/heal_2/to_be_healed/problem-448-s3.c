#include <stdio.h>
#include <stdlib.h>

unsigned long long calculate_perrin_sum(int n) {
    if (n < 0) {
        return 0;
    }

    unsigned long long total = 0;

    if (n == 1) {
        return 3;
    }

    if (n == 2) {
        return 3;
    }

    unsigned long long p0 = 3;
    unsigned long long p1 = 0;
    unsigned long long p2 = 2;

    total = p0 + p1 + p2;

    for (int i = 3; i < n; i++) {
        unsigned long long p3 = p0 + p1;
        total += p3;
        p0 = p1;
        p1 = p2;
        p2 = p3;
    }

    return total;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    long val = strtol(argv[1], NULL, 10);
    if (val > 10000 || val < 0) {
        return EXIT_FAILURE;
    }

    unsigned long long result = calculate_perrin_sum((int)val);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}