#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int average_of_even_numbers(unsigned long long limit,
                                   unsigned long long *average)
{
    if (average == NULL || limit == 0 || limit % 2 != 0) {
        return -1;
    }

    *average = limit / 2 + 1;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    unsigned long long limit;
    unsigned long long average;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        fprintf(stderr, "Failed to read input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    limit = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        fprintf(stderr, "Invalid input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || limit == 0 || limit % 2 != 0) {
        fprintf(stderr, "Enter a positive even number.\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (average_of_even_numbers(limit, &average) != 0) {
        fprintf(stderr, "Unable to calculate the average.\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("%llu\n", average);
    free(input);
    return EXIT_SUCCESS;
}