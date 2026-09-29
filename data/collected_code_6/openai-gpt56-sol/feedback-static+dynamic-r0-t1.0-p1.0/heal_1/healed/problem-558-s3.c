#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t magnitude(int64_t value)
{
    return value < 0
               ? (uint64_t)(-(value + INT64_C(1))) + UINT64_C(1)
               : (uint64_t)value;
}

static uint64_t digit_distance(int64_t first, int64_t second)
{
    uint64_t left = magnitude(first);
    uint64_t right = magnitude(second);
    uint64_t distance = 0;

    do {
        uint64_t left_digit = left % UINT64_C(10);
        uint64_t right_digit = right % UINT64_C(10);

        distance += left_digit > right_digit
                        ? left_digit - right_digit
                        : right_digit - left_digit;

        left /= UINT64_C(10);
        right /= UINT64_C(10);
    } while (left != 0 || right != 0);

    return distance;
}

static int parse_int64(const char **input, int64_t *value)
{
    char *end;

    errno = 0;
    *value = strtoimax(*input, &end, 10);

    if (end == *input || errno == ERANGE) {
        return 0;
    }

    *input = end;
    return 1;
}

int main(void)
{
    char input[256];
    const char *cursor;
    int64_t first;
    int64_t second;
    int extra;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_int64(&cursor, &first) ||
        !parse_int64(&cursor, &second) ||
        sscanf(cursor, " %c", (char *)&extra) == 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", digit_distance(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}