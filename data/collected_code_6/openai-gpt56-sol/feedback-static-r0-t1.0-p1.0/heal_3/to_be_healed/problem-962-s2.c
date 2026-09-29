#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_even_natural_numbers(uint64_t left, uint64_t right,
                                    uint64_t *result)
{
    uint64_t first;
    uint64_t last;
    uint64_t count;
    uint64_t half;
    uint64_t factor;

    if (result == NULL || left == 0 || left > right) {
        return 0;
    }

    if ((left & UINT64_C(1)) != 0) {
        if (left == UINT64_MAX) {
            *result = 0;
            return 1;
        }
        first = left + UINT64_C(1);
    } else {
        first = left;
    }

    last = right - (right & UINT64_C(1));

    if (first > last) {
        *result = 0;
        return 1;
    }

    count = (last - first) / UINT64_C(2) + UINT64_C(1);

    if ((count & UINT64_C(1)) == 0) {
        half = count / UINT64_C(2);

        if (first > UINT64_MAX - last) {
            return 0;
        }

        factor = first + last;
    } else {
        half = first / UINT64_C(2) + last / UINT64_C(2);
        factor = count;
    }

    if (half != 0 && factor > UINT64_MAX / half) {
        return 0;
    }

    *result = half * factor;
    return 1;
}

static int parse_uint64(const char **cursor, uint64_t *value)
{
    const char *start;
    char *end;
    uintmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    start = *cursor;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *cursor = end;
    return 1;
}

static int read_range(uint64_t *left, uint64_t *right)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    const char *cursor;
    size_t length;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (left == NULL || right == NULL) {
        return 0;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 0;
    }

    length = 0;
    while (length < sizeof input && input[length] != '\0') {
        ++length;
    }

    if (length == sizeof input) {
        return 0;
    }

    if (length == 0 || input[length - 1] != '\n') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            return 0;
        }
    }

    cursor = input;

    if (!parse_uint64(&cursor, left) || !parse_uint64(&cursor, right)) {
        return 0;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    return *cursor == '\0';
}

int main(void)
{
    uint64_t left;
    uint64_t right;
    uint64_t sum;

    if (!read_range(&left, &right)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_even_natural_numbers(left, right, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}