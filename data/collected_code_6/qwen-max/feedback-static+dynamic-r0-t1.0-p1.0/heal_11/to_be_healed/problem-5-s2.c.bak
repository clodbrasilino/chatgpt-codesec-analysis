#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 153, got 29
  *  test case 0 failed: expected 3, got 1
  *  test case 2 failed: expected 2131, got 181
  */

int countWays(int n) {
    if (n % 2 != 0) return 0;
    if (n == 0) return 1;
    int a = 1, b = 1;
    for (int i = 2; i <= n / 2; i++) {
        int c = 4 * a + b;
        a = b;
        b = c;
    }
    return b;
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