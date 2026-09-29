#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 4, got 6
  *  test case 1 failed: expected 11, got 20
  *  test case 2 failed: expected 26, got 168
  */

unsigned long long eulerian_number(int n, int m) {
    if (n < 0 || m < 0 || m >= n) {
        return 0;
    }
    if (m == 0) {
        return 1;
    }
    int rows = n + 1;
    int cols = m + 1;
    unsigned long long *dp = (unsigned long long *)malloc(rows * cols * sizeof(unsigned long long));
    if (dp == NULL) {
        fprintf(stderr, "Allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dp[i * cols + j] = 0;
        }
    }
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i * cols] = 1;
        for (int j = 1; j < cols && j < i; j++) {
            dp[i * cols + j] = (i - j) * dp[(i - 1) * cols + j] + (j + 1) * dp[(i - 1) * cols + j - 1];
        }
    }
    unsigned long long result = dp[n * cols + m];
    free(dp);
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <m>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    if (n < 0 || m < 0) {
        fprintf(stderr, "n and m must be non-negative integers\n");
        return EXIT_FAILURE;
    }
    unsigned long long result = eulerian_number(n, m);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}