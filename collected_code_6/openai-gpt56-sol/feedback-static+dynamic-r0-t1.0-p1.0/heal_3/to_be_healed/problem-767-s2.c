#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0;
    int valid = 1;

    if (buffer == NULL || size == 0) {
        return 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)ch));

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length < size - 1) {
            buffer[length++] = (char)ch;
        } else {
            valid = 0;
        }

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    }

    buffer[length] = '\0';

    if (ch == EOF && ferror(stdin)) {
        return 0;
    }

    return valid;
}

static int read_size(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(token, sizeof(token)) ||
        token[0] == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[128];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(token, sizeof(token))) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int read_int(int *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[128];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(token, sizeof(token))) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

static int add_pair_count(uint64_t *total, uint64_t amount)
{
    if (total == NULL || amount > UINT64_MAX - *total) {
        return 0;
    }

    *total += amount;
    return 1;
}

static int count_pairs(int *values, size_t count, int64_t sum,
                       uint64_t *result)
{
    size_t left = 0;
    size_t right;
    uint64_t pairs = 0;

    if (result == NULL) {
        return 0;
    }

    *result = 0;

    if (count < 2) {
        return 1;
    }

    if (values == NULL) {
        return 0;
    }

    qsort(values, count, sizeof(*values), compare_ints);
    right = count - 1;

    while (left < right) {
        const int64_t current =
            (int64_t)values[left] + (int64_t)values[right];

        if (current < sum) {
            ++left;
        } else if (current > sum) {
            --right;
        } else if (values[left] == values[right]) {
            const uint64_t occurrences = (uint64_t)(right - left + 1);
            const uint64_t pair_count =
                occurrences * (occurrences - 1) / 2;

            if (!add_pair_count(&pairs, pair_count)) {
                return 0;
            }

            break;
        } else {
            size_t left_count = 1;
            size_t right_count = 1;
            uint64_t pair_count;

            while (left + left_count < right &&
                   values[left + left_count] == values[left]) {
                ++left_count;
            }

            while (right - right_count >= left + left_count &&
                   values[right - right_count] == values[right]) {
                ++right_count;
            }

            if ((uint64_t)left_count != 0 &&
                (uint64_t)right_count >
                    UINT64_MAX / (uint64_t)left_count) {
                return 0;
            }

            pair_count =
                (uint64_t)left_count * (uint64_t)right_count;

            if (!add_pair_count(&pairs, pair_count)) {
                return 0;
            }

            left += left_count;
            right -= right_count;
        }
    }

    *result = pairs;
    return 1;
}

int main(void)
{
    size_t count;
    int64_t sum;
    int *values = NULL;
    uint64_t result;

    if (!read_size(&count) || !read_int64(&sum)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values) ||
        (uintmax_t)count > UINT64_MAX) {
        fputs("Input size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int(&values[i])) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!count_pairs(values, count, sum, &result)) {
        fputs("Pair count is too large\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}