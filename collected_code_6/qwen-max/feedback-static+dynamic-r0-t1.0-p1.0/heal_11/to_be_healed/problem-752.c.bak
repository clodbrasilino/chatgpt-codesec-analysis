#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 5, got 17
  *  test case 1 failed: expected 1, got 3
  *  test case 0 failed: expected 11, got 41
  */

long long jacobsthal(int n) {
    if (n == 0) return 1;
    if (n == 1) return 1;
    long long a = 1, b = 1;
    for (int i = 2; i <= n; ++i) {
        long long c = a + 2 * b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }
    printf("The %dth Jacobsthal number is: %lld\n", n, jacobsthal(n));
    return EXIT_SUCCESS;
}