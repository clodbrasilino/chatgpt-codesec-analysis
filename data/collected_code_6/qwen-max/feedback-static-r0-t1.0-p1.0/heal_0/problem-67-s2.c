#include <stdio.h>
#include <stdlib.h>

unsigned long long bell_number(int n) {
    unsigned long long bell[n+1][n+1];
    int i, j;

    bell[0][0] = 1;
    for (i = 1; i <= n; i++) {
        bell[i][0] = bell[i-1][i-1];
        for (j = 1; j <= i; j++)
            bell[i][j] = bell[i-1][j-1] + bell[i][j-1];
    }
    return bell[n][0];
}

int main() {
    int n;
    printf("Enter the number of elements in the set: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = bell_number(n);
    printf("The number of ways to partition a set of %d elements is: %llu\n", n, result);

    return EXIT_SUCCESS;
}