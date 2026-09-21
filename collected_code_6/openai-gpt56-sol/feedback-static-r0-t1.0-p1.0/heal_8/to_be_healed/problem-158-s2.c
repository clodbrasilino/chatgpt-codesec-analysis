#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>

static int compare_int64(const void *left, const void *right)
{
    const int64_t a = *(const int64_t *)left;
    const int64_t b = *(const int64_t *)right;

    return (a > b) - (a < b);
}

static int read_size(size_t *value)
{
    uintmax_t parsed;
    int result;

    if (value == NULL) {
        return 0;
    }

    errno = 0;
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    result = scanf("%" SCNuMAX, &parsed);

    if (result != 1 || errno == ERANGE ||
        parsed == UINTMAX_C(0) ||
        parsed > (uintmax_t)SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    intmax_t parsed;
    int result;

    if (value == NULL) {
        return 0;
    }

    errno = 0;
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    result = scanf("%" SCNdMAX, &parsed);

    if (result != 1 || errno == ERANGE ||
        parsed < (intmax_t)INT64_MIN ||
        parsed > (intmax_t)INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static uint64_t absolute_difference(int64_t left, int64_t right)
{
    const uint64_t unsigned_left = (uint64_t)left;
    const uint64_t unsigned_right = (uint64_t)right;

    return left >= right
        ? unsigned_left - unsigned_right
        : unsigned_right - unsigned_left;
}

static int calculate_operations(int64_t *values, size_t count,
                                uint64_t *operations)
{
    uint64_t total = UINT64_C(0);
    int64_t target;

    if (values == NULL || operations == NULL || count == 0U) {
        return 0;
    }

    qsort(values, count, sizeof(*values), compare_int64);
    target = values[count / 2U];

    for (size_t i = 0U; i < count; ++i) {
        uint64_t difference = absolute_difference(values[i], target);

        if (difference > UINT64_MAX - total) {
            return 0;
        }

        total += difference;
    }

    *operations = total;
    return 1;
}

int main(void)
{
    size_t count;
    int64_t *values;
    uint64_t operations;

    if (!read_size(&count) ||
        count > SIZE_MAX / sizeof(*values)) {
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (!read_int64(&values[i])) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!calculate_operations(values, count, &operations)) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);

    if (printf("%" PRIu64 "\n", operations) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}