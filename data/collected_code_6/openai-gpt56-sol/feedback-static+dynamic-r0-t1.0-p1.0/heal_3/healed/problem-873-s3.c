#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int fibonacci(unsigned int n, uint64_t *result)
{
    uint64_t first = 0;
    uint64_t second = 1;

    if (result == NULL) {
        return 0;
    }

    for (unsigned int i = 0; i < n; ++i) {
        if (UINT64_MAX - first < second) {
            return 0;
        }

        uint64_t next = first + second;
        first = second;
        second = next;
    }

    *result = first;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long value;
    uint64_t result;

    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL ? argv[0] : "fibonacci";
        fprintf(stderr, "Usage: %s <integer from 0 to 93>\n", program);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoul(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        argv[1][0] == '-' ||
        value > 93UL) {
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