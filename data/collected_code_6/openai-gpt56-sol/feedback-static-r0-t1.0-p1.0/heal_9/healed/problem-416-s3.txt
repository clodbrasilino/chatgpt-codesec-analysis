#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t maximum_sum(uint64_t n)
{
    if (n < 12) {
        return n;
    }

    uint64_t a = maximum_sum(n / 2);
    uint64_t b = maximum_sum(n / 3);
    uint64_t c = maximum_sum(n / 4);

    if (a > UINT64_MAX - b) {
        return UINT64_MAX;
    }

    uint64_t sum = a + b;

    if (c > UINT64_MAX - sum) {
        return UINT64_MAX;
    }

    sum += c;
    return sum > n ? sum : n;
}

int main(void)
{
    char buffer[128];

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = 0;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        length++;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';

        int ch;
        do {
            ch = fgetc(stdin);
        } while (ch != EOF && ch != '\n');

        if (ch != EOF) {
            return EXIT_FAILURE;
        }
    } else {
        int ch = fgetc(stdin);
        if (ch != EOF) {
            return EXIT_FAILURE;
        }
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    char *start = buffer;

    while (*start == ' ' || *start == '\t' || *start == '\r' ||
           *start == '\v' || *start == '\f') {
        start++;
    }

    if (*start == '\0' || *start == '-') {
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || value > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\v' || *end == '\f') {
        end++;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    uint64_t result = maximum_sum((uint64_t)value);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}