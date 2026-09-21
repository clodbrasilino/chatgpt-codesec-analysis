#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
    intmax_t parsed;

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

int main(void)
{
    char *buffer = NULL;
    size_t capacity = 0;
    ssize_t length;
    const char *input;
    int64_t first;
    int64_t second;
    char extra;

    length = getline(&buffer, &capacity, stdin);
    if (length < 0) {
        free(buffer);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    input = buffer;

    if (!parse_int64(&input, &first) ||
        !parse_int64(&input, &second) ||
        sscanf(input, " %c", &extra) == 1) {
        free(buffer);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(buffer);

    if (printf("%" PRIu64 "\n", digit_distance(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}