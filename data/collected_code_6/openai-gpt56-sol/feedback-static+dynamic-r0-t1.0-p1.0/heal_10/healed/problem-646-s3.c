#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_INPUT_LENGTH = 4096 };

static int count_cubes(uint64_t n, uint64_t k, uint64_t *result)
{
    uint64_t per_side;
    uint64_t square;

    if (result == NULL || k == 0 || k > n) {
        return 0;
    }

    per_side = n / k;

    if (per_side > UINT64_MAX / per_side) {
        return 0;
    }

    square = per_side * per_side;

    if (square > UINT64_MAX / per_side) {
        return 0;
    }

    *result = square * per_side;
    return 1;
}

static int is_space(unsigned char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int parse_uint64(const char **input, uint64_t *value)
{
    const char *start;
    char *end;
    uintmax_t parsed;

    if (input == NULL || *input == NULL || value == NULL) {
        return 0;
    }

    while (is_space((unsigned char)**input)) {
        ++*input;
    }

    start = *input;

    if (*start == '\0' || *start == '-' || *start == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *input = end;
    return 1;
}

static int discard_remainder_of_line(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ch == '\n' || !ferror(stdin);
}

static int read_line(char *buffer, size_t size)
{
    size_t length;

    if (buffer == NULL || size < 2 || size > (size_t)INT_MAX) {
        return 0;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    for (length = 0;
         buffer[length] != '\0' && buffer[length] != '\n';
         ++length) {
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return 1;
    }

    if (feof(stdin)) {
        return length > 0;
    }

    if (!discard_remainder_of_line()) {
        return 0;
    }

    return 0;
}

int main(void)
{
    char *input;
    const char *cursor;
    uint64_t n;
    uint64_t k;
    uint64_t result;
    int status = EXIT_FAILURE;

    input = malloc((size_t)MAX_INPUT_LENGTH + 2U);
    if (input == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_line(input, (size_t)MAX_INPUT_LENGTH + 2U)) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    cursor = input;

    if (!parse_uint64(&cursor, &n) || !parse_uint64(&cursor, &k)) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    while (is_space((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    if (!count_cubes(n, k, &result)) {
        fputs("Invalid dimensions or result overflow\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}