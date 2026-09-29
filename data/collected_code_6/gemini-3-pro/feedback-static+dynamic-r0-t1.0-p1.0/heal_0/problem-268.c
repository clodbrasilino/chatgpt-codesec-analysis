#include <stdio.h>
#include <stdlib.h>

long long findStarNumber(int n) {
    if (n <= 0) {
        return -1;
    }
    return 6LL * n * (n - 1) + 1;
}

int main() {
    int n;
    long long starNumber;

    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    starNumber = findStarNumber(n);

    if (starNumber == -1) {
        fprintf(stderr, "Input must be a positive integer\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", starNumber);

    return EXIT_SUCCESS;
}