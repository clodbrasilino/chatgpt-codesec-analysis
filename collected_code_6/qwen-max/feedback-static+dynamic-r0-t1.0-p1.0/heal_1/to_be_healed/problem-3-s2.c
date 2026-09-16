#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got 1
  *  test case 1 failed: expected True, got 0
  *  test case 2 failed: expected True, got 0
  */

bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

void identify_non_primes(int limit) {
    for (int i = 0; i <= limit; ++i) {
        if (!is_prime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int limit = 20;
    identify_non_primes(limit);
    return 0;
}