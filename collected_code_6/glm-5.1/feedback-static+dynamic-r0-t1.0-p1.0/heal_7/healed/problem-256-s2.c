#include <stdio.h>
#include <stdlib.h>

int countPrimes(int n) {
    if (n <= 2) {
        return 0;
    }
    char *isPrime = malloc(n * sizeof(char));
    if (isPrime == NULL) {
        return -1;
    }
    for (int i = 2; i < n; i++) {
        isPrime[i] = 1;
    }
    for (int i = 2; i * i < n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j < n; j += i) {
                isPrime[j] = 0;
            }
        }
    }
    int count = 0;
    for (int i = 2; i < n; i++) {
        if (isPrime[i]) {
            count++;
        }
    }
    free(isPrime);
    return count;
}

int main(int argc, char * const * const argv) {
    int n = 10;
    if (argc == 2) {
        long val = strtol(argv[1], NULL, 10);
        if (val >= 0 && val <= 2147483647) {
            n = (int)val;
        } else {
            return 1;
        }
    }
    int result = countPrimes(n);
    if (result < 0) {
        return 1;
    }
    printf("%d\n", result);
    return 0;
}