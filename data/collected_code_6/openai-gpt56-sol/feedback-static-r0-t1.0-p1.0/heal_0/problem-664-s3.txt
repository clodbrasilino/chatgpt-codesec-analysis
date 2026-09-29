#include <errno.h>
#include <limits.h>
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
    char input[128];
    char *end = NULL;
    unsigned long long limit;
    unsigned long long average;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    limit = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || limit == 0 || limit % 2 != 0) {
        fprintf(stderr, "Enter a positive even number.\n");
        return EXIT_FAILURE;
    }

    if (average_of_even_numbers(limit, &average) != 0) {
        fprintf(stderr, "Unable to calculate the average.\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", average);
    return EXIT_SUCCESS;
}