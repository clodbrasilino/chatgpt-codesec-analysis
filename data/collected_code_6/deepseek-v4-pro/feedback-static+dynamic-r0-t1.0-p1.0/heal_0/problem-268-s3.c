#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long int nth_star_number(int n) {
    if (n < 0) {
        errno = EINVAL;
        return -1;
    }

    if (n > (INT_MAX - 1) / 6) {
        errno = ERANGE;
        return -1;
    }

    long long int result = 6LL * n * (n - 1) + 1;
    return result;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    long long int star = nth_star_number(n);

    if (errno == EINVAL) {
        fprintf(stderr, "Error: n must be non-negative\n");
        return EXIT_FAILURE;
    }

    if (errno == ERANGE) {
        fprintf(stderr, "Error: result overflow\n");
        return EXIT_FAILURE;
    }

    printf("Star number %d = %lld\n", n, star);
    return EXIT_SUCCESS;
}