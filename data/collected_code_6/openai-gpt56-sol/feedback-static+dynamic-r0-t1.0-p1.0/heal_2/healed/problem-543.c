#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int add_int64(int64_t a, int64_t b, int64_t *sum)
{
    if (sum == NULL) {
        return 0;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *sum = a + b;
    return 1;
}

static size_t digit_count(int64_t value)
{
    uint64_t magnitude;
    size_t count = 1U;

    if (value < 0) {
        magnitude = (uint64_t)(-(value + INT64_C(1))) + UINT64_C(1);
    } else {
        magnitude = (uint64_t)value;
    }

    while (magnitude >= UINT64_C(10)) {
        magnitude /= UINT64_C(10);
        ++count;
    }

    return count;
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

    *value = (int64_t)parsed;
    *input = end;
    return 1;
}

static int discard_line(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || feof(stdin);
}

int main(void)
{
    char input[256];
    const char *cursor;
    int64_t first;
    int64_t second;
    int64_t sum;

    if (fputs("Enter two integers: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        discard_line();
        fputs("Input too long.\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_int64(&cursor, &first) ||
        !parse_int64(&cursor, &second)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*cursor == ' ' || *cursor == '\t' ||
           *cursor == '\r' || *cursor == '\n' ||
           *cursor == '\v' || *cursor == '\f') {
        ++cursor;
    }

    if (*cursor != '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!add_int64(first, second, &sum)) {
        fputs("Integer overflow.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Sum: %" PRId64 "\nDigits: %zu\n",
               sum, digit_count(sum)) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}