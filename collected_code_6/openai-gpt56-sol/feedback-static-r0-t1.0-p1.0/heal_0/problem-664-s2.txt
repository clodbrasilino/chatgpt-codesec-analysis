#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int average_of_evens(unsigned long long limit, double *average)
{
    if (average == NULL || limit == 0U || limit % 2U != 0U) {
        return -1;
    }

    *average = ((double)limit + 2.0) / 2.0;
    return 0;
}

int main(void)
{
    char input[128];
    char *end = NULL;
    unsigned long long limit;
    double average;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    limit = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (average_of_evens(limit, &average) != 0) {
        fputs("Enter a positive even number.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%.2f\n", average);
    return EXIT_SUCCESS;
}