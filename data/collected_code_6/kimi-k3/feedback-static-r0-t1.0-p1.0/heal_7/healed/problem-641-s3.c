#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long nonagonal_number(int n) {
    if (n < 0) {
        return -1;
    }
    return (long long)n * (7LL * n - 5) / 2;
}

int main(void) {
    int n;
    char *buffer = NULL;
    size_t buffer_size = 0;
    char *endptr;
    long val;

    printf("Enter the value of n: ");

    if (getline(&buffer, &buffer_size, stdin) == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);

    if (errno == ERANGE || val > INT_MAX || val < 0) {
        fprintf(stderr, "Invalid input: out of range\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input: not a valid integer\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    n = (int)val;

    printf("Nonagonal number for n=%d is %lld\n", n, nonagonal_number(n));

    free(buffer);
    return EXIT_SUCCESS;
}