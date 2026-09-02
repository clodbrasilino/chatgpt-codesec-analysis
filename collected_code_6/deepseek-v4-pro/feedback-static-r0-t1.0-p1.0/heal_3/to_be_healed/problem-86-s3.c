#include <stdio.h>
#include <stdlib.h>

long long centered_hexagonal(int n) {
    if (n <= 0) {
        return -1;
    }
    return 3LL * n * (n - 1) + 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || endptr == argv[1] || val <= 0 || val > 1000000) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    int n = (int)val;
    long long result = centered_hexagonal(n);

    printf("%lld\n", result);

    return 0;
}