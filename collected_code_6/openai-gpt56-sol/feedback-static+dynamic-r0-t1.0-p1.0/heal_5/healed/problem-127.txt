#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
            (right < 0 && right < INT64_MAX / left)) {
            return 0;
        }
    }

    *result = left * right;
    return 1;
#endif
}

static int parse_int64_line(int64_t *left, int64_t *right)
{
    char line[256];
    char *cursor;
    char *end;
    intmax_t parsed;

    if (left == NULL || right == NULL) {
        return 0;
    }

    if (fgets(line, sizeof line, stdin) == NULL) {
        return 0;
    }

    if (strchr(line, '\n') == NULL && !feof(stdin)) {
        int ch;

        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }
        return 0;
    }

    cursor = line;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    parsed = strtoimax(cursor, &end, 10);
    if (end == cursor || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }
    *left = (int64_t)parsed;
    cursor = end;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    parsed = strtoimax(cursor, &end, 10);
    if (end == cursor || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }
    *right = (int64_t)parsed;
    cursor = end;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        return 0;
    }

    while (fgets(line, sizeof line, stdin) != NULL) {
        cursor = line;

        while (isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor != '\0') {
            return 0;
        }
    }

    return !ferror(stdin);
}

int main(void)
{
    int64_t left;
    int64_t right;
    int64_t result;

    if (!parse_int64_line(&left, &right)) {
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