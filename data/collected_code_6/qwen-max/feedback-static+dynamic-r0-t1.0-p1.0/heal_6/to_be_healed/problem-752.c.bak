#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 11, got 5
  *  test case 2 failed: expected 5, got 3
  */

long long jacobsthal(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 1;
    long long a = 0, b = 1, c = 1;
    for (int i = 3; i <= n; ++i) {
        long long temp = c;
        c = a + 2 * b;
        a = b;
        b = temp;
    }
    return c;
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