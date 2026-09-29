#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int find_nth_non_multiple(uint64_t n, uint64_t divisor,
                                 uint64_t *result)
{
    uint64_t block;
    uint64_t offset;

    if (n == 0 || divisor <= 1 || result == NULL) {
        return 0;
    }

    block = (n - 1) / (divisor - 1);
    offset = (n - 1) % (divisor - 1) + 1;

    if (block > (UINT64_MAX - offset) / divisor) {
        return 0;
    }

    *result = block * divisor + offset;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    char *line = NULL;
    char *end;
    size_t capacity = 0;
    ssize_t length;
    uintmax_t parsed;

    if (value == NULL) {
        return 0;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return 0;
    }

    errno = 0;
    end = line;
    parsed = strtoumax(end, &end, 10);

    if (errno == ERANGE || end == line || parsed > UINT64_MAX) {
        free(line);
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = (uint64_t)parsed;
    free(line);
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t divisor;
    uint64_t result;

    if (!read_uint64(&n) || !read_uint64(&divisor)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find_nth_non_multiple(n, divisor, &result)) {
        fputs("Unable to compute result\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}