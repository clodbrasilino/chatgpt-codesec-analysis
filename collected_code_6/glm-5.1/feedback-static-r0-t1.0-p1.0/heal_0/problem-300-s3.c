#include <stdio.h>
#include <stdlib.h>

long long binomial_coefficient(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    if (k > n - k) k = n - k;
    long long res = 1;
    for (int i = 0; i < k; i++) {
        if (res > (res * (n - i)) / (i + 1)) {
            return 0;
        }
        res = res * (n - i) / (i + 1);
    }
    return res;
}

long long count_binary_sequences(int n) {
    if (n < 0) return 0;
    long long total = 0;
    for (int i = 0; i <= n; i++) {
        long long ways = binomial_coefficient(n, i);
        if (ways == 0 && n > 0 && i <= n) {
            fprintf(stderr, "Overflow detected\n");
            return -1;
        }
        total += ways * ways;
        if (total < 0) {
            fprintf(stderr, "Overflow detected\n");
            return -1;
        }
    }
    return total;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > 30) {
        fprintf(stderr, "Invalid input: n must be a non-negative integer <= 30\n");
        return 1;
    }
    long long result = count_binary_sequences((int)val);
    if (result < 0) {
        return 1;
    }
    printf("%lld\n", result);
    return 0;
}