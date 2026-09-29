#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got 1
  *  test case 1 failed: expected True, got 0
  *  test case 2 failed: expected True, got 0
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

void find_non_primes(int start, int end) {
    bool found = false;
    for (int i = start; i <= end; i++) {
        if (!is_prime(i)) {
            printf("%d ", i);
            found = true;
        }
    }
    if (found) {
        printf("\n");
    } else {
        printf("No non-primes found\n");
    }
}

int main() {
    find_non_primes(1, 50);
    return 0;
}