#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

unsigned long long binom(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;
    unsigned long long res = 1;
    for (int i = 0; i < k; i++) {
        if (res > ULLONG_MAX / (n - i)) return 0;
        res = res * (n - i) / (i + 1);
    }
    return res;
}

unsigned long long sum_squares_binom(int n) {
    unsigned long long sum = 0;
    for (int k = 0; k <= n; k++) {
        unsigned long long b = binom(n, k);
        if (b != 0) {
            if (b > ULLONG_MAX / b) return 0;
            unsigned long long sq = b * b;
            if (sum > ULLONG_MAX - sq) return 0;
            sum += sq;
        }
    }
    return sum;
}

int main(void) {
    char buffer[1024];
    char *endptr;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    size_t len = strnlen(buffer, sizeof(buffer));

    if (len == sizeof(buffer) && buffer[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        if (c == EOF && ferror(stdin)) {
            clearerr(stdin);
        }
        return 1;
    }

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        return 1;
    }

    errno = 0;
    long val = strtol(buffer, &endptr, 10);
    if (endptr == buffer || *endptr != '\0') {
        return 1;
    }
    if (errno == ERANGE || val < 0 || val > INT_MAX) {
        return 1;
    }

    int n = (int)val;

    unsigned long long result = sum_squares_binom(n);
    printf("%llu\n", result);

    return 0;
}