#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void findMultiples(int n, int m) {
    for (int i = 1; i <= m; ++i) {
        long long product = (long long)n * i;
        if (product > INT_MAX || product < INT_MIN) {
            fprintf(stderr, "Integer overflow detected.\n");
            exit(EXIT_FAILURE);
        }
        printf("%d ", (int)product);
    }
    printf("\n");
}

int main() {
    int n, m;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input for n.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the number of multiples (m): ");
    if (scanf("%d", &m) != 1) {
        fprintf(stderr, "Invalid input for m.\n");
        return EXIT_FAILURE;
    }

    if (n <= 0 || m <= 0) {
        fprintf(stderr, "Both n and m must be positive integers.\n");
        return EXIT_FAILURE;
    }

    findMultiples(n, m);
    return EXIT_SUCCESS;
}