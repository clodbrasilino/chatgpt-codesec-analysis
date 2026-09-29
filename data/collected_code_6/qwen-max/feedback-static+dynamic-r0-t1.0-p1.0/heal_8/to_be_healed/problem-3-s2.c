#include <stdio.h>
#include <stdbool.h>
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

void identify_primes(int limit) {
    for (int i = 0; i <= limit; ++i) {
        if (is_prime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int limit = 20;
    identify_primes(limit);
    return 0;
}