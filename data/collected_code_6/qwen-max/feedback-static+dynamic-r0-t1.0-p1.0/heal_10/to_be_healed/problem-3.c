#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected True, got <no output>
  *  test case 0 failed: expected False, got <no output>
  *  test case 2 failed: expected True, got <no output>
  */

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

void identify_non_primes(int n, int* non_primes, int* count) {
    *count = 0;
    for (int i = 0; i < n; ++i) {
        if (!is_prime(i)) {
            non_primes[(*count)++] = i;
        }
    }
}

int main() {
    int n = 50;
    int* non_primes = (int*)malloc(n * sizeof(int));
    if (non_primes == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    int count = 0;
    identify_non_primes(n, non_primes, &count);

    for (int i = 0; i < count; ++i) {
        printf("%d ", non_primes[i]);
    }
    printf("\n");

    free(non_primes);
    return 0;
}