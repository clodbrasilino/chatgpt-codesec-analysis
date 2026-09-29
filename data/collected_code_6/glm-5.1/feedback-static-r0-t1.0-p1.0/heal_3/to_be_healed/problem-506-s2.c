#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long permutation(int n, int k) {
    unsigned long long result = 1;
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    for (int i = 0; i < k; i++) {
        if (result > ULLONG_MAX / (unsigned long long)(n - i)) {
            return 0;
        }
        result *= (unsigned long long)(n - i);
    }
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return 1;
    }
    
    char *endptr1;
    errno = 0;
    long val1 = strtol(argv[1], &endptr1, 10);
    if (errno != 0 || endptr1 == argv[1] || *endptr1 != '\0' || val1 < 0 || val1 > INT_MAX) {
        fprintf(stderr, "Invalid n\n");
        return 1;
    }
    int n = (int)val1;

    char *endptr2;
    errno = 0;
    long val2 = strtol(argv[2], &endptr2, 10);
    if (errno != 0 || endptr2 == argv[2] || *endptr2 != '\0' || val2 < 0 || val2 > INT_MAX) {
        fprintf(stderr, "Invalid k\n");
        return 1;
    }
    int k = (int)val2;

    unsigned long long res = permutation(n, k);
    printf("%llu\n", res);
    return 0;
}