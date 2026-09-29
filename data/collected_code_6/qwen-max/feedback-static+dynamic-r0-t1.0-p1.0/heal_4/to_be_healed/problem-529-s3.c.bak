#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 17, got 7
  *  test case 0 failed: expected 31, got 11
  *  test case 1 failed: expected 5, got 3
  */

int nth_jacobsthal_lucas(int n) {
    if (n == 0) return 2;
    if (n == 1) return 1;

    int a = 2, b = 1;
    for (int i = 2; i <= n; i++) {
        int c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return EXIT_FAILURE;
    }

    int result = nth_jacobsthal_lucas(n);
    printf("The %dth Jacobsthal-Lucas number is: %d\n", n, result);

    return EXIT_SUCCESS;
}