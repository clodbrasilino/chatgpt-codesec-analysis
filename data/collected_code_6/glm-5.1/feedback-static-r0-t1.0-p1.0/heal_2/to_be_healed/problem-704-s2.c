#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

double harmonic_sum(int n) {
    if (n < 1) {
        return 0.0;
    }
    double sum = 0.0;
    for (int i = 1; i <= n; i++) {
        sum += 1.0 / i;
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE || val < 1 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int n = (int)val;
    double result = harmonic_sum(n);
    printf("%.15f\n", result);
    return EXIT_SUCCESS;
}