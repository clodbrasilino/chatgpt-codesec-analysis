#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int tiling(int n) {
    if (n < 1) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    if (n == 2) {
        return 2;
    }
    
    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 1;
    dp[1] = 2;

    for (int i = 2; i < n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    int result = dp[n - 1];
    free(dp);

    return result;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <length>\n", argv[0]);
        return 1;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (errno == ERANGE || val > INT_MAX || val <= 0 || *endptr != '\0') {
        fprintf(stderr, "Length must be a positive integer within valid range.\n");
        return 1;
    }
    int n = (int)val;

    int result = tiling(n);
    if (result == -1) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    printf("%d\n", result);

    return 0;
}