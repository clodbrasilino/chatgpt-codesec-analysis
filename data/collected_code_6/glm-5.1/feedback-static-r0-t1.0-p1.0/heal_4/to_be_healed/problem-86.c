#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long centered_hexical(int n) {
    if (n < 1) {
        return 0;
    }
    return (unsigned long long)(3 * n - 2) * n;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || val < 1 || val > INT_MAX) {
        return EXIT_FAILURE;
    }

    unsigned long long result = centered_hexical((int)val);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}