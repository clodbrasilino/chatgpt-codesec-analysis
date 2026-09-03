#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int f(int n, int *memo) {
    if (n < 2) return n;

    if (memo[n] != -1) return memo[n];

    int a = f(n / 2, memo);
    int b = f(n / 3, memo);
    int c = f(n / 4, memo);
    int d = f(n / 5, memo);

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 270904543 + 2079268783 cannot be represented in type 'int'
     * UBSan: signed integer overflow: 1857144159 + 489414292 cannot be represented in type 'int'
     * UBSan: signed integer overflow: 1654103639 + 999056760 cannot be represented in type 'int'
     */
    int val = max(n, a + b + c + d);
    memo[n] = val;
    return val;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    int *memo = (int *)calloc(n + 1, sizeof(int));
    for (int i = 0; i <= n; ++i) {
        memo[i] = -1;
    }

    int result = f(n, memo);
    printf("Maximum sum possible: %d\n", result);

    free(memo);
    return 0;
}