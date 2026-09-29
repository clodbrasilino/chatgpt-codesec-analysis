#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int tiling_ways(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    int *dp = (int *)malloc((n + 1) * sizeof(int));
    if (dp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    if (n >= 1) {
        dp[1] = 1;
    }
    if (n >= 2) {
        dp[2] = 2;
    }
    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    int result = dp[n];
    free(dp);
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int n = (int)val;
    int ways = tiling_ways(n);
    printf("%d\n", ways);
    return EXIT_SUCCESS;
}