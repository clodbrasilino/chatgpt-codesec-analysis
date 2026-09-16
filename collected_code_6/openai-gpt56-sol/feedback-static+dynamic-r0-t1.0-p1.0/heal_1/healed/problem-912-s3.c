#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int lobb_number(unsigned int n, unsigned int m, uint64_t *result)
{
    uint64_t *values;
    size_t count;

    if (result == NULL || n == 0U || m > n) {
        return -1;
    }

    count = (size_t)n + 1U;
    if (count == 0U || count > SIZE_MAX / sizeof(*values)) {
        return -1;
    }

    values = calloc(count, sizeof(*values));
    if (values == NULL) {
        return -1;
    }

    values[0] = UINT64_C(1);

    for (unsigned int i = 1U; i <= n; ++i) {
        uint64_t previous = values[0];

        for (unsigned int j = 1U; j <= i; ++j) {
            uint64_t current = values[j];

            if (previous > UINT64_MAX - values[j]) {
                free(values);
                return -1;
            }

            values[j] += previous;
            previous = current;
        }
    }

    {
        uint64_t next = m < n ? values[m + 1U] : UINT64_C(0);
        uint64_t difference;
        uint64_t factor;

        if (values[m] < next) {
            free(values);
            return -1;
        }

        difference = values[m] - next;

        if ((uint64_t)m > (UINT64_MAX - UINT64_C(1)) / UINT64_C(2)) {
            free(values);
            return -1;
        }

        factor = UINT64_C(2) * (uint64_t)m + UINT64_C(1);

        if (difference != 0U && factor > UINT64_MAX / difference) {
            free(values);
            return -1;
        }

        *result = difference * factor;
    }

    free(values);
    return 0;
}

static int parse_unsigned(const char *text, unsigned int *value)
{
    char *end;
    unsigned long parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoul(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > (unsigned long)UINT_MAX) {
        return -1;
    }

    *value = (unsigned int)parsed;
    return 0;
}

int main(int argc, char *const argv[])
{
    unsigned int n;
    unsigned int m;
    uint64_t result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s n m\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_unsigned(argv[1], &n) != 0 ||
        parse_unsigned(argv[2], &m) != 0 ||
        n == 0U || m > n) {
        fputs("Invalid arguments\n", stderr);
        return EXIT_FAILURE;
    }

    if (lobb_number(n, m, &result) != 0) {
        fputs("Unable to calculate Lobb number\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}