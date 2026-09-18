#include <stdio.h>
#include <limits.h>

int count_domino_tilings(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    if (n == 1) return 0;
    if (n == 2) return 3;

    long long prev2 = 1;
    long long prev1 = 0;
    long long current = 3;

    for (int i = 3; i <= n; i++) {
        long long next = 4 * current - prev2;
        if (next > INT_MAX) return 0;
        prev2 = prev1;
        prev1 = current;
        current = next;
    }

    return (int)current;
}

int main(void) {
    int n;
    printf("Enter board length n (3 x n board): ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (n < 0) {
        printf("Board length cannot be negative.\n");
        return 0;
    }

    int result = count_domino_tilings(n);
    printf("Number of ways to tile a 3 x %d board: %d\n", n, result);

    return 0;
}