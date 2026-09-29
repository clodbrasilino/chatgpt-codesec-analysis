#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 5, got 15
  *  test case 2 failed: expected 15, got 52
  *  test case 0 failed: expected 2, got 5
  */

unsigned long long bellNumber(int n) {
    unsigned long long **bell = (unsigned long long **)calloc(n + 1, sizeof(unsigned long long *));
    if (bell == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= n; i++) {
        bell[i] = (unsigned long long *)calloc(n + 1, sizeof(unsigned long long));
        if (bell[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (int j = 0; j < i; j++) free(bell[j]);
            free(bell);
            exit(EXIT_FAILURE);
        }
    }
    bell[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        bell[i][0] = bell[i - 1][i - 1];
        for (int j = 1; j <= i; j++)
            bell[i][j] = bell[i - 1][j - 1] + bell[i][j - 1];
    }
    unsigned long long result = bell[n][n];
    for (int i = 0; i <= n; i++) free(bell[i]);
    free(bell);
    return result;
}

int main() {
    char input[16];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    int n;
    if (sscanf(input, "%d", &n) != 1 || n < 0 || n > INT_MAX / 2) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }
    unsigned long long result = bellNumber(n);
    printf("The %dth Bell number is: %llu\n", n, result);
    return EXIT_SUCCESS;
}