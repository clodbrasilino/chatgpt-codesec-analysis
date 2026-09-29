#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint64_t magnitude(int64_t value)
{
    if (value >= 0) {
        return (uint64_t)value;
    }

    return (uint64_t)(-(value + INT64_C(1))) + UINT64_C(1);
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 6, got <no output>
  *  test case 2 failed: expected 7, got <no output>
  */

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

static int read_int64(const char **cursor, int64_t *value)
{
    char *end;
    intmax_t parsed;

    errno = 0;
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    const char *cursor;
    int64_t first;
    int64_t second;
    char extra;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    cursor = input;

    if (!read_int64(&cursor, &first) ||
        !read_int64(&cursor, &second) ||
        sscanf(cursor, " %c", &extra) == 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", digit_distance(first, second)) < 0) {
        return 1;
    }

    return 0;
}