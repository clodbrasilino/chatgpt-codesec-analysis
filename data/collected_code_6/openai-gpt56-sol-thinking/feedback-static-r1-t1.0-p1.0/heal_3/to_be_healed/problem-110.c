#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t start;
    int64_t end;
} Range;

typedef enum {
    RANGE_STATUS_OK,
    RANGE_STATUS_INVALID_ARGUMENT,
    RANGE_STATUS_ALLOCATION_FAILURE,
    RANGE_STATUS_SIZE_OVERFLOW
} RangeStatus;

static int compare_int64(const void *left, const void *right)
{
    const int64_t a = *(const int64_t *)left;
    const int64_t b = *(const int64_t *)right;

    return (a > b) - (a < b);
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end = NULL;
    intmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static RangeStatus extract_missing_ranges(const int64_t *values,
                                          size_t value_count,
                                          int64_t range_start,
                                          int64_t range_end,
                                          Range **missing_ranges,
                                          size_t *missing_count)
{
    int64_t *sorted_values = NULL;
    Range *ranges = NULL;
    size_t range_count = 0;
    int64_t current;
    int completed = 0;

    if (missing_ranges == NULL || missing_count == NULL ||
        (value_count != 0 && values == NULL) ||
        range_start > range_end) {
        return RANGE_STATUS_INVALID_ARGUMENT;
    }

    *missing_ranges = NULL;
    *missing_count = 0;

    if (value_count > SIZE_MAX / sizeof(*sorted_values) ||
        value_count > (SIZE_MAX / sizeof(*ranges)) - 1) {
        return RANGE_STATUS_SIZE_OVERFLOW;
    }

    if (value_count != 0) {
        sorted_values = malloc(value_count * sizeof(*sorted_values));
        if (sorted_values == NULL) {
            return RANGE_STATUS_ALLOCATION_FAILURE;
        }

        for (size_t i = 0; i < value_count; ++i) {
            sorted_values[i] = values[i];
        }

        qsort(sorted_values, value_count, sizeof(*sorted_values),
              compare_int64);
    }

    ranges = malloc((value_count + 1) * sizeof(*ranges));
    if (ranges == NULL) {
        free(sorted_values);
        return RANGE_STATUS_ALLOCATION_FAILURE;
    }

    current = range_start;

    for (size_t i = 0; i < value_count; ++i) {
        const int64_t value = sorted_values[i];

        if (value < current) {
            continue;
        }

        if (value > range_end) {
            break;
        }

        if (value > current) {
            ranges[range_count].start = current;
            ranges[range_count].end = value - 1;
            ++range_count;
        }

        if (value == range_end) {
            completed = 1;
            break;
        }

        current = value + 1;
    }

    if (!completed && current <= range_end) {
        ranges[range_count].start = current;
        ranges[range_count].end = range_end;
        ++range_count;
    }

    free(sorted_values);

    if (range_count == 0) {
        free(ranges);
        return RANGE_STATUS_OK;
    }

    *missing_ranges = ranges;
    *missing_count = range_count;

    return RANGE_STATUS_OK;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    int64_t range_start;
    int64_t range_end;
    int64_t *values = NULL;
    Range *missing_ranges = NULL;
    size_t value_count;
    size_t missing_count = 0;
    RangeStatus status;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <start> <end> [values...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_int64(argv[1], &range_start) ||
        !parse_int64(argv[2], &range_end) ||
        range_start > range_end) {
        fprintf(stderr, "Invalid range\n");
        return EXIT_FAILURE;
    }

    value_count = (size_t)(argc - 3);

    if (value_count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    if (value_count != 0) {
        values = malloc(value_count * sizeof(*values));
        if (values == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < value_count; ++i) {
            if (!parse_int64(argv[i + 3], &values[i])) {
                fprintf(stderr, "Invalid value: %s\n", argv[i + 3]);
                free(values);
                return EXIT_FAILURE;
            }
        }
    }

    status = extract_missing_ranges(values, value_count, range_start, range_end,
                                    &missing_ranges, &missing_count);
    free(values);

    if (status != RANGE_STATUS_OK) {
        switch (status) {
        case RANGE_STATUS_ALLOCATION_FAILURE:
            fprintf(stderr, "Memory allocation failed\n");
            break;
        case RANGE_STATUS_SIZE_OVERFLOW:
            fprintf(stderr, "Input is too large\n");
            break;
        default:
            fprintf(stderr, "Invalid arguments\n");
            break;
        }

        free(missing_ranges);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < missing_count; ++i) {
        int result;

        if (missing_ranges[i].start == missing_ranges[i].end) {
            result = printf("%" PRId64 "\n", missing_ranges[i].start);
        } else {
            result = printf("%" PRId64 "->%" PRId64 "\n",
                            missing_ranges[i].start,
                            missing_ranges[i].end);
        }

        if (result < 0) {
            free(missing_ranges);
            return EXIT_FAILURE;
        }
    }

    free(missing_ranges);
    return EXIT_SUCCESS;
}