#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int multiply_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

#if defined(__GNUC__) || defined(__clang__)
    return !__builtin_mul_overflow(left, right, result);
#else
    if (left > 0) {
        if ((right > 0 && left > INT64_MAX / right) ||
            (right < 0 && right < INT64_MIN / left)) {
            return 0;
        }
    } else if (left < 0) {
        if ((right > 0 && left < INT64_MIN / right) ||
            (right < 0 && left < INT64_MAX / right)) {
            return 0;
        }
    }

    *result = left * right;
    return 1;
#endif
}

static int parse_int64(const char **input, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (input == NULL || *input == NULL || value == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(*input, &end, 10);

    if (end == *input || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *input = end;
    *value = (int64_t)parsed;
    return 1;
}

static int read_line(char *buffer, size_t size)
{
    int ch;

    if (buffer == NULL || size < 2 ||
        fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    if (strchr(buffer, '\n') != NULL) {
        return 1;
    }

    if (feof(stdin)) {
        return 1;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return 0;
}

int main(void)
{
    char input[256];
    const char *cursor;
    int64_t left;
    int64_t right;
    int64_t result;

    if (!read_line(input, sizeof input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_int64(&cursor, &left) ||
        !parse_int64(&cursor, &right)) {
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

    if (!multiply_int64(left, right, &result)) {
        fputs("Multiplication overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}