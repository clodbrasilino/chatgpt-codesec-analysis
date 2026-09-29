#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

void find_multiples(int n, int m) {
    int i;
    for (i = 1; i <= m; i++) {
        long long result = (long long)n * i;
        if (printf("%lld ", result) < 0) {
            exit(EXIT_FAILURE);
        }
    }
    if (printf("\n") < 0) {
        exit(EXIT_FAILURE);
    }
}

int main(void) {
    int n, m;
    char *endptr;
    char buffer[256];
    long val;

    printf("Enter the number (n): ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer || *endptr != '\n' || val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }
    n = (int)val;

    printf("Enter the number of multiples (m): ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer || *endptr != '\n' || val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Invalid input for m\n");
        return EXIT_FAILURE;
    }
    m = (int)val;

    if (m <= 0) {
        fprintf(stderr, "m must be positive\n");
        return EXIT_FAILURE;
    }

    find_multiples(n, m);

    return EXIT_SUCCESS;
}