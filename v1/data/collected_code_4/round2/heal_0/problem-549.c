#include <stdio.h>
#include <stdlib.h>

long long int find_sum(int n) {
    long long int sum = 0, i, j, val;

    for (i = 1; i <= n; i++) {
        val = 1;
        for (j = 1; j <= 5; j++)
            val *= (2 * i - 1);
        sum += val;
    }

    return sum;
}

int main() {
    int n;
    long long int result;

    printf("Enter the number of terms: ");
    if (scanf("%d", &n) != 1) {
        printf("Error: Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        printf("Error: Negative number entered\n");
        return EXIT_FAILURE;
    }

    result = find_sum(n);

    if (result < 0) {
        printf("Overflow error: Number is too large\n");
        return EXIT_FAILURE;
    }

    printf("Sum of 5th powers of first %d odd numbers is %lld\n", n, result);

    return EXIT_SUCCESS;
}