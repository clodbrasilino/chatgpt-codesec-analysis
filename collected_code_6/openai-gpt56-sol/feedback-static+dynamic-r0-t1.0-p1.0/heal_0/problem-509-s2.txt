#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int average_of_odds(unsigned long long limit, long double *average)
{
    unsigned long long count;

    if (average == NULL || limit == 0U || limit % 2U == 0U) {
        return -1;
    }

    count = limit / 2U + 1U;
    *average = (long double)count;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long long limit;
    long double average;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive odd number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    limit = strtoull(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || limit == 0U || limit % 2U == 0U) {
        fprintf(stderr, "Invalid input: enter a positive odd integer.\n");
        return EXIT_FAILURE;
    }

    if (average_of_odds(limit, &average) != 0) {
        fprintf(stderr, "Unable to calculate the average.\n");
        return EXIT_FAILURE;
    }

    printf("Average: %.0Lf\n", average);
    return EXIT_SUCCESS;
}