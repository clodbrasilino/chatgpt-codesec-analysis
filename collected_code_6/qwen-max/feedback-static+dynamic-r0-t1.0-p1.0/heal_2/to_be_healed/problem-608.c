#include <stdio.h>
#include <stdlib.h>

int binomial_coefficient(int n, int k) {
    long long res = 1;
    if (k > n - k) k = n - k;
    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return (int)res;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got 1
  *  test case 1 failed: expected 5, got 1
  *  test case 0 failed: expected 2, got 1
  */

int bell_number(int n) {
    int bell[n+1][n+1];
    for (int i = 0; i <= n; ++i) {
        bell[0][i] = 0;
        bell[i][0] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++)
            bell[i][j] = bell[i-1][j-1] + bell[i-1][j];
    }

    return bell[n][0];
}

int main() {
    int n;
    printf("Enter the value of n to find nth Bell number: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    printf("The %dth Bell number is: %d\n", n, bell_number(n));
    return EXIT_SUCCESS;
}