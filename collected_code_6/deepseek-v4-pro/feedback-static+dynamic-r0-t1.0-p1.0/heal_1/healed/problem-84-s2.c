#include <stdio.h>
#include <stdlib.h>

int newman_conway(int n, int *memo) {
    if (n < 1) {
        return 0;
    }
    if (n == 1 || n == 2) {
        return 1;
    }
    if (memo[n] != 0) {
        return memo[n];
    }
    int prev = newman_conway(n - 1, memo);
    memo[n] = newman_conway(prev, memo) + newman_conway(n - prev, memo);
    return memo[n];
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (n < 1) {
        fprintf(stderr, "n must be positive\n");
        return 1;
    }
    int *memo = calloc(n + 1, sizeof(int));
    if (memo == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    printf("%d\n", newman_conway(n, memo));
    free(memo);
    return 0;
}