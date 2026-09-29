#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int sum_odd_factors(int n) {
    if (n <= 0) {
        return 0;
    }
    int sum = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i % 2 != 0) {
                sum += i;
            }
            if (i != n / i) {
                if ((n / i) % 2 != 0) {
                    sum += n / i;
                }
            }
        }
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    errno = 0;
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val <= 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int n = (int)val;
    int result = sum_odd_factors(n);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}