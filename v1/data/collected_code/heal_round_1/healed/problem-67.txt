#include <stdio.h>

int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int bellNumbers(int n) {
    int bell[n + 1][n + 1];
    bell[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        bell[i][0] = bell[i - 1][i - 1];

        for (int j = 1; j <= i; j++) {
            bell[i][j] = bell[i - 1][j - 1] + bell[i][j - 1];
        }
    }

    return bell[n][0];
}

int main() {
    int n = 0;
    printf("Enter the number of bell numbers: ");
    scanf("%d", &n);
    printf("Number of ways to partition a set of %d bell numbers: %d", n, bellNumbers(n));

    return 0;
}