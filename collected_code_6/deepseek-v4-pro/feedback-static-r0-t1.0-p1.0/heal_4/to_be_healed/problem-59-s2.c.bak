#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long octagonal_number(int n) {
    if (n <= 0) {
        return -1;
    }
    return (long long)n * (3LL * n - 2LL);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n;
    long long result;
    const char *const usage = "Usage: %s <n>\n";

    if (argc != 2) {
        fprintf(stderr, usage, argv[0]);
        return 1;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Error: n must be a positive integer\n");
        return 1;
    }

    if (val <= 0 || val > INT_MAX) {
        fprintf(stderr, "Error: n must be a positive integer\n");
        return 1;
    }

    n = (int)val;
    result = octagonal_number(n);

    if (result < 0) {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }

    printf("%lld\n", result);
    return 0;
}