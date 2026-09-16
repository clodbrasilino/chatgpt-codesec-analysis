#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int fibonacci(unsigned int n, unsigned long long *result)
{
    unsigned long long previous = 0ULL;
    unsigned long long current = 1ULL;

    if (result == NULL) {
        return 0;
    }

    for (unsigned int i = 0U; i < n; ++i) {
        if (ULLONG_MAX - previous < current) {
            return 0;
        }

        unsigned long long next = previous + current;
        previous = current;
        current = next;
    }

    *result = previous;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long input;
    unsigned long long result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer from 0 to 93>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoul(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' || input > 93UL) {
        fprintf(stderr, "Invalid input: expected an integer from 0 to 93\n");
        return EXIT_FAILURE;
    }

    if (!fibonacci((unsigned int)input, &result)) {
        fprintf(stderr, "Unable to calculate Fibonacci number\n");
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}