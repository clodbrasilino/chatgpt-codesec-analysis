#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long sum_of_squares_even(int n)
{
    unsigned long long sum = 0;
    int i;

    for (i = 1; i <= n; i++) {
        unsigned long long even = (unsigned long long)i * 2;
        sum += even * even;
    }

    return sum;
}

int main(void)
{
    char *input = NULL;
    size_t input_size = 0;
    ssize_t bytes_read;
    char *endptr;
    long value;
    int n;

    bytes_read = getline(&input, &input_size, stdin);
    if (bytes_read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtol(input, &endptr, 10);

    if (errno == ERANGE || value > INT_MAX || value < 0) {
        fprintf(stderr, "Invalid input: out of range\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (endptr == input) {
        fprintf(stderr, "Invalid input: not a number\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (*endptr != '\n' && *endptr != '\0') {
        fprintf(stderr, "Invalid input: trailing characters\n");
        free(input);
        return EXIT_FAILURE;
    }

    n = (int)value;
    printf("%llu\n", sum_of_squares_even(n));

    free(input);
    return EXIT_SUCCESS;
}