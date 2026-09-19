#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 17, got 22
  *  test case 1 failed: expected 5, got 4
  *  test case 0 failed: expected 31, got 53
  */

long long jacobsthal_lucas(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: negative input not allowed\n");
        exit(EXIT_FAILURE);
    }
    if (n == 0) return 2;
    if (n == 1) return 1;
    
    long long prev2 = 2;
    long long prev1 = 1;
    long long current = 0;
    
    for (int i = 2; i <= n; i++) {
        if (prev1 > (LLONG_MAX - 2 * prev2)) {
            fprintf(stderr, "Error: integer overflow would occur\n");
            exit(EXIT_FAILURE);
        }
        current = 2 * prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    
    return current;
}

int main(void) {
    int n;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Jacobsthal-Lucas(%d) = %lld\n", n, jacobsthal_lucas(n));
    
    return EXIT_SUCCESS;
}