#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_even_index_binomial_coefficients(uint32_t n, uint64_t *result)
{
    if (result == NULL || n > 64U) {
        return -1;
    }

    *result = (n == 0U) ? UINT64_C(1)
                        : (UINT64_C(1) << (n - 1U));

    return 0;
}

static int discard_line(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ch;
}

static int read_value(uint32_t *result)
{
    char buffer[128];
    char *end;
    uintmax_t value;
    int terminator;

    if (result == NULL) {
        return -1;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    end = buffer;
    while (*end != '\0' && *end != '\n') {
        ++end;
    }

    if (*end == '\n') {
        *end = '\0';
    } else if (!feof(stdin)) {
        terminator = discard_line();
        if (terminator == EOF && ferror(stdin)) {
            return -1;
        }
        return -1;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || value > UINT32_MAX) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\v' ||
           *end == '\f' || *end == '\r') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *result = (uint32_t)value;
    return 0;
}

int main(void)
{
    uint32_t value;
    uint64_t sum;

    if (read_value(&value) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_even_index_binomial_coefficients(value, &sum) != 0) {
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}