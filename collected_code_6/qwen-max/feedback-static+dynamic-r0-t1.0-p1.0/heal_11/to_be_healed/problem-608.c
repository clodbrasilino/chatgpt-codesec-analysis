#include <stdio.h>
#include <stdlib.h>

long long binomial_coefficient(int n, int k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    if (k > n - k) k = n - k;
    long long res = 1;
    for (int i = 0; i < k; ++i) {
        res = res * (n - i) / (i + 1);
    }
    return res;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got <no output>
  *  test case 0 failed: expected 2, got <no output>
  *  test case 1 failed: expected 5, got <no output>
  */

long long bell_number(int n) {
    long long **bell = (long long **)malloc((n+1) * sizeof(long long *));
    for (int i = 0; i <= n; ++i) {
        bell[i] = (long long *)calloc(i+1, sizeof(long long));
        bell[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            bell[i][j] = bell[i-1][j-1] + bell[i-1][j] * j;
    }

    long long result = 0;
    for (int i = 0; i <= n; ++i) {
        result += bell[n][i];
    }
    for (int i = 0; i <= n; ++i) {
        free(bell[i]);
    }
    free(bell);

    return result;
}

int main() {
    int n;
    printf("Enter the value of n to find nth Bell number: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    printf("The %dth Bell number is: %lld\n", n, bell_number(n));
    return EXIT_SUCCESS;
}