#include <stdio.h>
#include <stdbool.h>

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
  *  test case 0 failed: expected 17, got <no output>
  *  test case 1 failed: expected 77, got <no output>
  *  test case 2 failed: expected 10, got <no output>
  */

long long sum_of_primes(int n) {
    long long sum = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime(i)) {
            sum += i;
        }
    }
    return sum;
}

int main(void) {
    int n;
    printf("Enter a number: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (n < 1) {
        fprintf(stderr, "Number must be at least 1\n");
        return 1;
    }
    printf("Sum of primes between 1 and %d: %lld\n", n, sum_of_primes(n));
    return 0;
}