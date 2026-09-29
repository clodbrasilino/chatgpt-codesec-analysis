#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>

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
        if (b != 0 && sum > ULLONG_MAX - b * b) return 0;
        sum += b * b;
    }
    return sum;
}

int main(void) {
    char buffer[256];
    char *endptr;
    long val;
    size_t len;
    int c;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    len = strnlen(buffer, sizeof(buffer));
    if (len == 0 || len >= sizeof(buffer)) {
        return 1;
    }

    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    } else {
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    for (size_t i = 0; i < len; i++) {
        if (buffer[i] == '\0' || buffer[i] == '\n' || buffer[i] == '\r') {
            buffer[i] = '\0';
            len = i;
            break;
        }
    }

    if (len == 0) {
        return 1;
    }

    for (size_t i = 0; i < len; i++) {
        if ((unsigned char)buffer[i] > 127 || buffer[i] < '0' || buffer[i] > '9') {
            if (i == 0 && buffer[i] == '+') continue;
            if (i == 0 && buffer[i] == '-') continue;
            return 1;
        }
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);
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