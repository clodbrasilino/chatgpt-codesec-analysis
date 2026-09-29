#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int decagonal_number(uint64_t n, uint64_t *result)
{
    if (result == NULL || n == 0 || n > UINT64_MAX / 4) {
        return 0;
    }

    uint64_t factor = 4 * n - 3;

    if (n > UINT64_MAX / factor) {
        return 0;
    }

    *result = n * factor;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    if (value == NULL) {
        return 0;
    }

    errno = 0;
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return 0;
    }

    char *start = line;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(line);
        return 0;
    }

    char *end = NULL;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > UINT64_MAX) {
        free(line);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
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
    uint64_t result;

    if (!read_uint64(&n)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!decagonal_number(n, &result)) {
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}