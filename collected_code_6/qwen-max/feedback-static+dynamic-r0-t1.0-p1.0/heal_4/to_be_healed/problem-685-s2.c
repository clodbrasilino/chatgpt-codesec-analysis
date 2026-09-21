#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>

bool is_prime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 10, got <no output>
  *  test case 0 failed: expected 17, got <no output>
  *  test case 1 failed: expected 77, got <no output>
  */

int sum_of_primes(int n) {
    int sum = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime(i)) {
            if (sum > INT_MAX - i) {
                printf("Integer overflow detected. Aborting.\n");
                return -1;
            }
            sum += i;
        }
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    while (scanf("%d", &n) != 1 || n < 1) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (getchar() != '\n');
        printf("Invalid input. Please enter a positive integer.\n");
    }
    int result = sum_of_primes(n);
    if (result != -1) {
        printf("Sum of prime numbers between 1 and %d is: %d\n", n, result);
    }
    return 0;
}