#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

static bool differ_by_one_bit(uint64_t first, uint64_t second)
{
    uint64_t difference = first ^ second;

    return difference != UINT64_C(0) &&
           (difference & (difference - UINT64_C(1))) == UINT64_C(0);
}

static bool parse_uint64(const char **input, uint64_t *value)
{
    char *end;
    uintmax_t result;

    while (isspace((unsigned char)**input)) {
        ++*input;
    }

    if (**input == '\0' || **input == '-') {
        return false;
    }

    errno = 0;
    result = strtoumax(*input, &end, 10);

    if (end == *input || errno == ERANGE || result > UINT64_MAX) {
        return false;
    }

    *value = (uint64_t)result;
    *input = end;
    return true;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    const char *cursor;
    uint64_t first;
    uint64_t second;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_uint64(&cursor, &first) ||
        !parse_uint64(&cursor, &second)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);
    puts(differ_by_one_bit(first, second) ? "Yes" : "No");

    return EXIT_SUCCESS;
}