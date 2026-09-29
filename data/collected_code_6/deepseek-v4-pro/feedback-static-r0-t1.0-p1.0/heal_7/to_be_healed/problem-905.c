#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

unsigned long long binom(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;
    unsigned long long res = 1;
    for (int i = 0; i < k; i++) {
        if (res > (unsigned long long)-1 / (n - i)) return 0;
        res = res * (n - i) / (i + 1);
    }
    return res;
}

unsigned long long sum_squares_binom(int n) {
    unsigned long long sum = 0;
    for (int k = 0; k <= n; k++) {
        unsigned long long b = binom(n, k);
        if (b != 0 && sum > (unsigned long long)-1 - b * b) return 0;
        sum += b * b;
    }
    return sum;
}

int main(void) {
    int n;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *endptr;
    long val;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    } else if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        return 1;
    }

    if (len == 0) {
        return 1;
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);
    if (endptr == buffer || *endptr != '\0') {
        return 1;
    }
    if (errno == ERANGE || val < 0 || val > INT_MAX) {
        return 1;
    }
    n = (int)val;

    unsigned long long result = sum_squares_binom(n);
    printf("%llu\n", result);

    return 0;
}