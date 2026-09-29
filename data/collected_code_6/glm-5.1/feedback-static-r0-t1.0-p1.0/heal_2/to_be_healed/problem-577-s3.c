#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int last_factorial_digit(int n) {
    if (n < 0) {
        return -1;
    }
    if (n >= 5) {
        return 0;
    }
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result % 10;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int n = (int)val;
    int res = last_factorial_digit(n);
    if (res < 0) {
        return EXIT_FAILURE;
    }
    printf("%d\n", res);
    return EXIT_SUCCESS;
}