#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long sum_even_factors(long long n)
{
    long long sum = 0;
    long long i;
    long long abs_n;

    if (n == 0) {
        return 0;
    }

    abs_n = (n < 0) ? -n : n;

    if (abs_n % 2 != 0) {
        return 0;
    }

    for (i = 2; i <= abs_n / 2; i += 2) {
        if (abs_n % i == 0) {
            if (sum > LLONG_MAX - i) {
                return -1;
            }
            sum += i;
        }
    }

    if (sum > LLONG_MAX - abs_n) {
        return -1;
    }
    sum += abs_n;

    return sum;
}

int main(void)
{
    char *input = NULL;
    size_t input_size = 0;
    ssize_t input_length;
    char *endptr;
    long long number;
    long long result;

    printf("Enter a number: ");

    input_length = getline(&input, &input_size, stdin);

    if (input_length == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoll(input, &endptr, 10);

    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (endptr == input) {
        fprintf(stderr, "Invalid input: not a number\n");
        free(input);
        return EXIT_FAILURE;
    }

    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n') {
        endptr++;
    }

    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input: trailing characters\n");
        free(input);
        return EXIT_FAILURE;
    }

    result = sum_even_factors(number);

    if (result == -1) {
        fprintf(stderr, "Overflow occurred during calculation\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Sum of even factors of %lld is: %lld\n", number, result);

    free(input);
    return EXIT_SUCCESS;
}