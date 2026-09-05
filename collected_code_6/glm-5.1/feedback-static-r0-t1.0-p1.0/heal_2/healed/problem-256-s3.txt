#include <stdio.h>
#include <stdlib.h>

int countPrimes(int n) {
    if (n <= 2) {
        return 0;
    }

    char *is_prime = (char *)malloc(n * sizeof(char));
    if (is_prime == NULL) {
        return 0;
    }

    for (int i = 2; i < n; i++) {
        is_prime[i] = 1;
    }

    for (int i = 2; i * i < n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j < n; j += i) {
                is_prime[j] = 0;
            }
        }
    }

    int count = 0;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            count++;
        }
    }

    free(is_prime);
    return count;
}

int main(int argc, char const * const *argv) {
    int n = 0;
    if (argc == 2) {
        long val = strtol(argv[1], NULL, 10);
        if (val >= 0 && val <= 2147483647) {
            n = (int)val;
        } else {
            return 1;
        }
    } else {
        printf("Enter a non-negative integer: ");
        if (scanf("%d", &n) != 1 || n < 0) {
            return 1;
        }
    }

    int result = countPrimes(n);
    printf("%d\n", result);

    return 0;
}