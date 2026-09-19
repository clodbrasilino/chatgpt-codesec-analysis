#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

void find_multiples(int n, int m) {
    for (int i = 1; i <= m; i++) {
        int64_t result = (int64_t)n * i;
        if (result > INT_MAX || result < INT_MIN) {
            fprintf(stderr, "Integer overflow detected\n");
            exit(EXIT_FAILURE);
        }
        printf("%lld ", (long long)result);
    }
    printf("\n");
}

int main(void) {
    int n, m;
    char *endptr;
    char buffer[256];
    long temp;

    printf("Enter the number (n): ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    temp = strtol(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer || *endptr != '\n' || temp > INT_MAX || temp < INT_MIN) {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }
    n = (int)temp;

    printf("Enter the number of multiples (m): ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    temp = strtol(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer || *endptr != '\n' || temp > INT_MAX || temp < INT_MIN) {
        fprintf(stderr, "Invalid input for m\n");
        return EXIT_FAILURE;
    }
    m = (int)temp;

    if (m <= 0) {
        fprintf(stderr, "m must be positive\n");
        return EXIT_FAILURE;
    }

    find_multiples(n, m);

    return EXIT_SUCCESS;
}