#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

double geometric_sum(int n) {
    if (n <= 1) {
        return 1.0;
    }
    double total = 0.0;
    double current = 1.0;
    for (int i = 0; i < n; i++) {
        total += current;
        current /= 2.0;
    }
    return total;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    double result = geometric_sum((int)val);
    printf("%f\n", result);
    return EXIT_SUCCESS;
}