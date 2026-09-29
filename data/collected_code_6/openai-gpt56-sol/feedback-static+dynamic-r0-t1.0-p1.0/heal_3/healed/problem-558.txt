#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint64_t magnitude(int64_t value)
{
    if (value >= 0) {
        return (uint64_t)value;
    }

    return (uint64_t)(-(value + INT64_C(1))) + UINT64_C(1);
}

static uint64_t digit_distance(int64_t first, int64_t second)
{
    uint64_t left = magnitude(first);
    uint64_t right = magnitude(second);
    uint64_t distance = 0;

    do {
        uint64_t left_digit = left % UINT64_C(10);
        uint64_t right_digit = right % UINT64_C(10);

        distance += left_digit >= right_digit
                        ? left_digit - right_digit
                        : right_digit - left_digit;

        left /= UINT64_C(10);
        right /= UINT64_C(10);
    } while (left != 0 || right != 0);

    return distance;
}

static int read_int64(const char **cursor, int64_t *value)
{
    char *end;
    intmax_t parsed;

    while (isspace((unsigned char)**cursor)) {
        ++*cursor;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(*cursor, &end, 10);

    if (end == *cursor || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    *cursor = end;
    return 1;
}

int main(void)
{
    char input[256];
    const char *cursor;
    int64_t first;
    int64_t second;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!read_int64(&cursor, &first) || !read_int64(&cursor, &second)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", digit_distance(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}