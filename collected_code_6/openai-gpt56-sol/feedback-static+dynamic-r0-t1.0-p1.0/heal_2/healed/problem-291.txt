#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_ways(size_t n, uint64_t k, uint64_t *result)
{
    if (result == NULL || n == 0 || k == 0) {
        return 0;
    }

    if (n == 1) {
        *result = k;
        return 1;
    }

    if (k > UINT64_MAX / k) {
        return 0;
    }

    uint64_t same = k;
    uint64_t different = k * (k - 1);

    for (size_t i = 3; i <= n; ++i) {
        if (same > UINT64_MAX - different) {
            return 0;
        }

        uint64_t total = same + different;

        if (k > 1 && total > UINT64_MAX / (k - 1)) {
            return 0;
        }

        same = different;
        different = total * (k - 1);
    }

    if (same > UINT64_MAX - different) {
        return 0;
    }

    *result = same + different;
    return 1;
}

static int read_input(size_t *n, uint64_t *k)
{
    if (n == NULL || k == NULL) {
        return 0;
    }

    char *line = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return 0;
    }

    char *cursor = line;
    char *end = NULL;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-') {
        free(line);
        return 0;
    }

    errno = 0;
    uintmax_t parsed_n = strtoumax(cursor, &end, 10);

    if (cursor == end || errno == ERANGE || parsed_n > SIZE_MAX) {
        free(line);
        return 0;
    }

    cursor = end;

    if (!isspace((unsigned char)*cursor)) {
        free(line);
        return 0;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-') {
        free(line);
        return 0;
    }

    errno = 0;
    uintmax_t parsed_k = strtoumax(cursor, &end, 10);

    if (cursor == end || errno == ERANGE || parsed_k > UINT64_MAX) {
        free(line);
        return 0;
    }

    cursor = end;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(line);
        return 0;
    }

    *n = (size_t)parsed_n;
    *k = (uint64_t)parsed_k;

    free(line);
    return 1;
}

int main(void)
{
    size_t n;
    uint64_t k;
    uint64_t result;

    if (!read_input(&n, &k)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!count_ways(n, k, &result)) {
        fputs("Invalid input or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}