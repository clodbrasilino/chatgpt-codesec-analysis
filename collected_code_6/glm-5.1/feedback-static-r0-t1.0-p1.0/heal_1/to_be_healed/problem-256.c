#include <stdio.h>
#include <stdlib.h>

int countPrimes(int n) {
    if (n <= 2) {
        return 0;
    }

    char *is_prime = (char *)malloc(n * sizeof(char));
    if (is_prime == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        is_prime[i] = 1;
    }

    is_prime[0] = 0;
    is_prime[1] = 0;

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
    is_prime = NULL;

    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n = 10;

    if (argc == 2) {
        long val = strtol(argv[1], NULL, 10);
        if (val >= 0 && val <= 2147483647) {
            n = (int)val;
        }
    }

    int result = countPrimes(n);
    if (result >= 0) {
        printf("%d\n", result);
    }

    return 0;
}