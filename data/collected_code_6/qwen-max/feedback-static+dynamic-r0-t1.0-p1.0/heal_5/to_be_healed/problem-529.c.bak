#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 31, got <no output>
  *  test case 2 failed: expected 17, got <no output>
  *  test case 1 failed: expected 5, got <no output>
  */

long long jacobsthal_lucas(long n) {
    if (n == 0) return 2;
    if (n == 1) return 1;

    long long a = 2, b = 1;
    for (long i = 2; i <= n; i++) {
        long long c = a + b * 2;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    long long result = jacobsthal_lucas(n);
    printf("The %ldth Jacobsthal-Lucas number is: %lld\n", n, result);
    return EXIT_SUCCESS;
}