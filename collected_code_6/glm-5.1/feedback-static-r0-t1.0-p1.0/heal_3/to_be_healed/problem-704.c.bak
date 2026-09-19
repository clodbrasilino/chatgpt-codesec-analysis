#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

double harmonic_sum(int n) {
    if (n <= 1) {
        return 0.0;
    }
    double sum = 0.0;
    int i;
    for (i = 1; i < n; i++) {
        sum += 1.0 / (double)i;
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (errno == ERANGE || *endptr != '\0' || val < 0 || val > INT_MAX) {
        fprintf(stderr, "Invalid input: must be a non-negative integer within range\n");
        return EXIT_FAILURE;
    }
    double result = harmonic_sum((int)val);
    printf("%.15f\n", result);
    return EXIT_SUCCESS;
}