#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long int star_number(int n) {
    if (n <= 0) {
        fprintf(stderr, "Error: n must be a positive integer\n");
        exit(EXIT_FAILURE);
    }

    if (n > 1 && (n - 1) > (LLONG_MAX / (6LL * n)) / (n - 1)) {
        fprintf(stderr, "Error: integer overflow detected\n");
        exit(EXIT_FAILURE);
    }

    return 6LL * n * (n - 1) + 1;
}

int main(void) {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    printf("Star number %d: %lld\n", n, star_number(n));
    return EXIT_SUCCESS;
}