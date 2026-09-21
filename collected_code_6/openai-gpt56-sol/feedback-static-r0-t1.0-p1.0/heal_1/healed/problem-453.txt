#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_even_factors(uint64_t number, uint64_t *sum)
{
    uint64_t total = 0;

    if (number == 0 || sum == NULL) {
        return -1;
    }

    for (uint64_t factor = 1; factor <= number / factor; ++factor) {
        if (number % factor != 0) {
            continue;
        }

        uint64_t paired_factor = number / factor;

        if ((factor & UINT64_C(1)) == 0) {
            if (factor > UINT64_MAX - total) {
                return -1;
            }
            total += factor;
        }

        if (paired_factor != factor &&
            (paired_factor & UINT64_C(1)) == 0) {
            if (paired_factor > UINT64_MAX - total) {
                return -1;
            }
            total += paired_factor;
        }
    }

    *sum = total;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end = NULL;
    uintmax_t parsed_number;
    uint64_t sum;
    int status = EXIT_FAILURE;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        fputs("Failed to read input.\n", stderr);
        goto cleanup;
    }

    errno = 0;
    parsed_number = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed_number == 0 ||
        parsed_number > UINT64_MAX) {
        fputs("Invalid number.\n", stderr);
        goto cleanup;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end == '\r') {
        ++end;
    }

    if (*end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid number.\n", stderr);
        goto cleanup;
    }

    if (sum_even_factors((uint64_t)parsed_number, &sum) != 0) {
        fputs("Unable to calculate the sum.\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}