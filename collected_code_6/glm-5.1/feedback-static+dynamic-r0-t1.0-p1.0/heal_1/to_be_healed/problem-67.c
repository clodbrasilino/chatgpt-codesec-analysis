#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 6775685320645824322581483068371419745979053216268760300, got <no output>
  *  test case 0 failed: expected 2, got <no output>
  *  test case 1 failed: expected 115975, got <no output>
  */

unsigned long long bell_number(int n) {
    unsigned long long *bell = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    if (bell == NULL) {
        exit(EXIT_FAILURE);
    }
    bell[0] = 1;
    for (int i = 1; i <= n; i++) {
        bell[i] = 0;
        for (int j = 0; j < i; j++) {
            bell[i] += bell[j] * bell[i - 1 - j] / (i - j);
        }
    }
    unsigned long long result = bell[n];
    free(bell);
    return result;
}

unsigned long long compute_bell(int n) {
    if (n < 0) {
        exit(EXIT_FAILURE);
    }
    unsigned long long **triangle = (unsigned long long **)malloc((n + 1) * sizeof(unsigned long long *));
    if (triangle == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= n; i++) {
        triangle[i] = (unsigned long long *)malloc((i + 1) * sizeof(unsigned long long));
        if (triangle[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(triangle[j]);
            }
            free(triangle);
            exit(EXIT_FAILURE);
        }
    }
    triangle[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        triangle[i][0] = triangle[i - 1][i - 1];
        for (int j = 1; j <= i; j++) {
            triangle[i][j] = triangle[i][j - 1] + triangle[i - 1][j - 1];
        }
    }
    unsigned long long res = triangle[n][0];
    for (int i = 0; i <= n; i++) {
        free(triangle[i]);
    }
    free(triangle);
    return res;
}

int main(void) {
    int n = 5;
    unsigned long long ways = compute_bell(n);
    printf("%llu\n", ways);
    return 0;
}