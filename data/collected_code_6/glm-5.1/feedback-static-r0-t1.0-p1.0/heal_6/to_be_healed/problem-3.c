#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int is_non_prime(int n) {
    if (n <= 1) {
        return 1;
    }
    if (n == 2) {
        return 0;
    }
    if (n % 2 == 0) {
        return 1;
    }
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return 1;
        }
    }
    return 0;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char const * const argv[const]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }
    for (int i = 1; i < argc; i++) {
        char *endptr;
        errno = 0;
        long val = strtol(argv[i], &endptr, 10);
        if (errno != 0 || *endptr != '\0' || val < 0 || val > INT_MAX) {
            return EXIT_FAILURE;
        }
        int num = (int)val;
        if (is_non_prime(num)) {
            printf("%d\n", num);
        }
    }
    return EXIT_SUCCESS;
}