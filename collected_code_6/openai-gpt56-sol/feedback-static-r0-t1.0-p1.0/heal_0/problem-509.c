#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int average_of_odds(long long limit, double *average)
{
    if (limit < 1 || (limit % 2) == 0 || average == NULL) {
        return -1;
    }

    unsigned long long count = ((unsigned long long)limit + 1ULL) / 2ULL;
    *average = (double)count;
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive odd number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    long long limit = strtoll(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        limit < 1 || (limit % 2) == 0) {
        fprintf(stderr, "Error: enter a valid positive odd number.\n");
        return EXIT_FAILURE;
    }

    double average = 0.0;

    if (average_of_odds(limit, &average) != 0) {
        fprintf(stderr, "Error: unable to calculate the average.\n");
        return EXIT_FAILURE;
    }

    printf("Average: %.2f\n", average);
    return EXIT_SUCCESS;
}