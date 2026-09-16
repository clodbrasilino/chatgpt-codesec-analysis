#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int fibonacci(unsigned int n, uint64_t *result)
{
    uint64_t first;
    uint64_t second;

    if (result == NULL) {
        return 0;
    }

    if (n < 2U) {
        *result = n;
        return 1;
    }

    if (!fibonacci(n - 1U, &first) || !fibonacci(n - 2U, &second)) {
        return 0;
    }

    if (UINT64_MAX - first < second) {
        return 0;
    }

    *result = first + second;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end;
    unsigned long value;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer from 0 to 93>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoul(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' || value > 93UL) {
        fprintf(stderr, "Invalid input: expected an integer from 0 to 93\n");
        return EXIT_FAILURE;
    }

    if (!fibonacci((unsigned int)value, &result)) {
        fprintf(stderr, "Failed to compute Fibonacci number\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}