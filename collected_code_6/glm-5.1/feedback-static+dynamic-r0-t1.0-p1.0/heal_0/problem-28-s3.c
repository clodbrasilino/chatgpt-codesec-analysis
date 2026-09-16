#include <stdio.h>
#include <stdlib.h>

int binomial_coefficient(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    if (k > n - k) {
        k = n - k;
    }
    long long res = 1;
    for (int i = 1; i <= k; i++) {
        if (res > (res * (n - k + i)) / i) { 
            return -1;
        }
        res = res * (n - k + i);
        res = res / i;
    }
    return (int)res;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return 1;
    }
    char *endptr_n, *endptr_k;
    long val_n = strtol(argv[1], &endptr_n, 10);
    long val_k = strtol(argv[2], &endptr_k, 10);
    if (*endptr_n != '\0' || *endptr_k != '\0' || val_n < 0 || val_k < 0) {
        fprintf(stderr, "Invalid input. n and k must be non-negative integers.\n");
        return 1;
    }
    int n = (int)val_n;
    int k = (int)val_k;
    int result = binomial_coefficient(n, k);
    if (result < 0) {
        fprintf(stderr, "Arithmetic overflow detected.\n");
        return 1;
    }
    printf("%d\n", result);
    return 0;
}