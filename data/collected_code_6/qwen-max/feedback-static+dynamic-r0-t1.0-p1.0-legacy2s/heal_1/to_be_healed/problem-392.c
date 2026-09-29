#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int f(int n, int *memo) {
    if (n == 0) return 0;
    if (memo[n] != -1) return memo[n];

    int option1 = n;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 268992052 + 1964506882 cannot be represented in type 'int'
     * UBSan: signed integer overflow: 1780119274 + 473196540 cannot be represented in type 'int'
     * UBSan: signed integer overflow: 1573198689 + 955137920 cannot be represented in type 'int'
     */
    int option2 = f(n / 2, memo) + f(n / 3, memo) + f(n / 4, memo) + f(n / 5, memo);
    memo[n] = max(option1, option2);

    return memo[n];
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    int *memo = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
        memo[i] = -1;
    }

    int result = f(n, memo);
    printf("Maximum sum: %d\n", result);

    free(memo);
    return 0;
}