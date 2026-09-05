#include <stdio.h>
#include <stdlib.h>

long long perrin(int n) {
    if (n == 0) {
        return 3;
    }
    if (n == 1) {
        return 0;
    }
    if (n == 2) {
        return 2;
    }
    return perrin(n - 2) + perrin(n - 3);
}

int main(void) {
    int n;
    long long result;

    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "n must be a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    result = perrin(n);
    printf("Perrin number %d is %lld\n", n, result);

    return EXIT_SUCCESS;
}