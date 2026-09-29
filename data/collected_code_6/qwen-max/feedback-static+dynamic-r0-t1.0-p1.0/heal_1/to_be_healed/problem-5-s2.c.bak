#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 153, got <no output>
  *  test case 2 failed: expected 2131, got <no output>
  *  test case 0 failed: expected 3, got <no output>
  */

int countWays(int n) {
    if (n == 0) return 1;
    if (n == 1) return 1;
    int a = 1, b = 1, c;
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = 2; i <= n; ++i) {
        c = a + b * 2;
        a = b;
        b = c;
    }
    /* Possible weaknesses found:
     *  Uninitialized variable: c [uninitvar]
     *  Uninitialized variable: c
     */
    return c;
}

int main() {
    int n;
    printf("Enter the length of the board (n): ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int result = countWays(n);
    printf("Number of ways to fill 3 x %d board with 2 x 1 dominoes: %d\n", n, result);
    return EXIT_SUCCESS;
}