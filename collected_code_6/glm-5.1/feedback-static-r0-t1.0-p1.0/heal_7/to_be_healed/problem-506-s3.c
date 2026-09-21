#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long permutation(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    unsigned long long result = 1;
    for (int i = 0; i < k; i++) {
        if (result > ULLONG_MAX / (unsigned long long)(n - i)) {
            exit(EXIT_FAILURE);
        }
        result *= (unsigned long long)(n - i);
    }
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[static const argc]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    errno = 0;
    char *endptr1;
    char *endptr2;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);
    if (errno != 0 || endptr1 == argv[1] || *endptr1 != '\0' || val1 < INT_MIN || val1 > INT_MAX) {
        return EXIT_FAILURE;
    }
    if (errno != 0 || endptr2 == argv[2] || *endptr2 != '\0' || val2 < INT_MIN || val2 > INT_MAX) {
        return EXIT_FAILURE;
    }
    int n = (int)val1;
    int k = (int)val2;
    unsigned long long res = permutation(n, k);
    printf("%llu\n", res);
    return EXIT_SUCCESS;
}