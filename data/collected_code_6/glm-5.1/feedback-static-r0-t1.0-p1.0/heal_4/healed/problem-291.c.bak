#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main(int argc, char * const * const argv) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    char *endptr1;
    errno = 0;
    long long val1 = strtoll(argv[1], &endptr1, 10);
    if (errno != 0 || *endptr1 != '\0' || val1 < 0) {
        return EXIT_FAILURE;
    }
    char *endptr2;
    errno = 0;
    long long val2 = strtoll(argv[2], &endptr2, 10);
    if (errno != 0 || *endptr2 != '\0' || val2 < 0) {
        return EXIT_FAILURE;
    }
    long long result = numWays(val1, val2);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}