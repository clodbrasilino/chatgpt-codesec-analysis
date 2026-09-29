#include <stdio.h>
#include <stdlib.h>

int binomial_coefficient(int n, int k) {
    int res = 1;
    if (k > n - k) k = n - k;
    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

int bell_number(int n) {
    int bell[n+1][n+1];
    bell[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        bell[i][0] = bell[i-1][i-1];

        for (int j = 1; j <= i; j++)
            bell[i][j] = bell[i-1][j-1] + bell[i][j-1];
    }

    return bell[n][0];
}

int main() {
    int n;
    printf("Enter the value of n to find nth Bell number: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    printf("The %dth Bell number is: %d\n", n, bell_number(n));
    return EXIT_SUCCESS;
}