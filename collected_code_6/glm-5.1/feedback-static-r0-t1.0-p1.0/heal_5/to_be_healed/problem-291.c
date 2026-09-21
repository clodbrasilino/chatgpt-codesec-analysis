#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long numWays(long long n, long long k) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return k;
    }
    if (k == 1) {
        if (n <= 2) {
            return 1;
        } else {
            return 0;
        }
    }
    long long same = k;
    long long diff = k * (k - 1);
    long long total = same + diff;
    for (long long i = 3; i <= n; i++) {
        same = diff;
        diff = total * (k - 1);
        total = same + diff;
    }
    return total;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    char *endptr_n;
    errno = 0;
    long long n = strtoll(argv[1], &endptr_n, 10);
    if (errno != 0 || *endptr_n != '\0' || n < 0 || argv[1][0] == '\0') {
        return EXIT_FAILURE;
    }
    char *endptr_k;
    errno = 0;
    long long k = strtoll(argv[2], &endptr_k, 10);
    if (errno != 0 || *endptr_k != '\0' || k < 0 || argv[2][0] == '\0') {
        return EXIT_FAILURE;
    }
    long long result = numWays(n, k);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}