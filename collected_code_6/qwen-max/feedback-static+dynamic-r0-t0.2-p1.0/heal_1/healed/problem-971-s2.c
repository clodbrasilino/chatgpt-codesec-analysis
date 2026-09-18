#include <stdio.h>
#include <stdlib.h>

int max_segments(int n, int a, int b, int c, int *memo) {
    if (n < 0) return -1;
    if (n == 0) return 0;
    if (memo[n] != -1) return memo[n];

    int max = -1;
    int result;

    result = max_segments(n - a, a, b, c, memo);
    if (result != -1 && result + 1 > max) max = result + 1;

    result = max_segments(n - b, a, b, c, memo);
    if (result != -1 && result + 1 > max) max = result + 1;

    result = max_segments(n - c, a, b, c, memo);
    if (result != -1 && result + 1 > max) max = result + 1;

    memo[n] = max;
    return max;
}

int main() {
    int n, a, b, c;
    printf("Enter the total length n: ");
    scanf("%d", &n);
    printf("Enter the segment lengths a, b, c: ");
    scanf("%d %d %d", &a, &b, &c);

    int *memo = (int *)calloc(n + 1, sizeof(int));
    for (int i = 0; i <= n; i++) {
        memo[i] = -1;
    }

    int result = max_segments(n, a, b, c, memo);
    if (result == -1) {
        printf("No segments can be formed.\n");
    } else {
        printf("Maximum number of segments: %d\n", result);
    }

    free(memo);
    return 0;
}