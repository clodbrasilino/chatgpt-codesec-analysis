#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t start;
    int64_t end;
} Range;

typedef enum {
    RANGE_SUCCESS = 0,
    RANGE_INVALID_ARGUMENT,
    RANGE_ALLOCATION_FAILURE,
    RANGE_SIZE_OVERFLOW
} RangeStatus;

static int compare_int64(const void *left, const void *right)
{
    const int64_t left_value = *(const int64_t *)left;
    const int64_t right_value = *(const int64_t *)right;

    if (left_value < right_value) {
        return -1;
    }

    if (left_value > right_value) {
        return 1;
    }

    return 0;
}

static int append_range(
    Range *ranges,
    size_t capacity,
    size_t *count,
    int64_t start,
    int64_t end)
{
    if (*count >= capacity) {
        return 0;
    }

    ranges[*count].start = start;
    ranges[*count].end = end;
    ++(*count);

    return 1;
}

RangeStatus extract_missing_ranges(
    const int64_t *values,
    size_t value_count,
    int64_t range_start,
    int64_t range_end,
    Range **missing_ranges,
    size_t *missing_count)
{
    int64_t *sorted_values = NULL;
    Range *ranges = NULL;
    size_t range_capacity;
    size_t result_count = 0;
    int64_t next_missing;
    int endpoint_covered = 0;

    if (missing_ranges == NULL || missing_count == NULL) {
        return RANGE_INVALID_ARGUMENT;
    }

    *missing_ranges = NULL;
    *missing_count = 0;

    if ((value_count != 0 && values == NULL) || range_start > range_end) {
        return RANGE_INVALID_ARGUMENT;
    }

    if (value_count > SIZE_MAX / sizeof(*sorted_values)) {
        return RANGE_SIZE_OVERFLOW;
    }

    if (value_count == SIZE_MAX) {
        return RANGE_SIZE_OVERFLOW;
    }

    range_capacity = value_count + 1;

    if (range_capacity > SIZE_MAX / sizeof(*ranges)) {
        return RANGE_SIZE_OVERFLOW;
    }

    if (value_count != 0) {
        sorted_values = malloc(value_count * sizeof(*sorted_values));
        if (sorted_values == NULL) {
            return RANGE_ALLOCATION_FAILURE;
        }

        for (size_t i = 0; i < value_count; ++i) {
            sorted_values[i] = values[i];
        }

        if (value_count > 1) {
            qsort(
                sorted_values,
                value_count,
                sizeof(*sorted_values),
                compare_int64
            );
        }
    }

    ranges = malloc(range_capacity * sizeof(*ranges));
    if (ranges == NULL) {
        free(sorted_values);
        return RANGE_ALLOCATION_FAILURE;
    }

    next_missing = range_start;

    for (size_t i = 0; i < value_count; ++i) {
        const int64_t value = sorted_values[i];

        if (value < range_start) {
            continue;
        }

        if (value > range_end) {
            break;
        }

        if (value < next_missing) {
            continue;
        }

        if (value > next_missing) {
            if (!append_range(
                    ranges,
                    range_capacity,
                    &result_count,
                    next_missing,
                    value - 1)) {
                free(sorted_values);
                free(ranges);
                return RANGE_SIZE_OVERFLOW;
            }
        }

        if (value == range_end) {
            endpoint_covered = 1;
            break;
        }

        next_missing = value + 1;
    }

    if (!endpoint_covered) {
        if (!append_range(
                ranges,
                range_capacity,
                &result_count,
                next_missing,
                range_end)) {
            free(sorted_values);
            free(ranges);
            return RANGE_SIZE_OVERFLOW;
        }
    }

    free(sorted_values);

    if (result_count == 0) {
        free(ranges);
        return RANGE_SUCCESS;
    }

    *missing_ranges = ranges;
    *missing_count = result_count;

    return RANGE_SUCCESS;
}

void free_missing_ranges(Range *ranges)
{
    free(ranges);
}

static const char *range_status_message(RangeStatus status)
{
    switch (status) {
        case RANGE_SUCCESS:
            return "success";
        case RANGE_INVALID_ARGUMENT:
            return "invalid argument";
        case RANGE_ALLOCATION_FAILURE:
            return "memory allocation failure";
        case RANGE_SIZE_OVERFLOW:
            return "size overflow";
        default:
            return "unknown error";
    }
}

int main(void)
{
    const int64_t values[] = {15, 3, 11, 6, 10, 8, 3};
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    const int64_t range_start = 1;
    const int64_t range_end = 20;
    Range *missing_ranges = NULL;
    size_t missing_count = 0;

    const RangeStatus status = extract_missing_ranges(
        values,
        value_count,
        range_start,
        range_end,
        &missing_ranges,
        &missing_count
    );

    if (status != RANGE_SUCCESS) {
        if (fprintf(stderr, "Error: %s\n", range_status_message(status)) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < missing_count; ++i) {
        int print_result;

        if (missing_ranges[i].start == missing_ranges[i].end) {
            print_result = printf(
                "%" PRId64 "\n",
                missing_ranges[i].start
            );
        } else {
            print_result = printf(
                "%" PRId64 "-%" PRId64 "\n",
                missing_ranges[i].start,
                missing_ranges[i].end
            );
        }

        if (print_result < 0) {
            free_missing_ranges(missing_ranges);
            return EXIT_FAILURE;
        }
    }

    free_missing_ranges(missing_ranges);
    return EXIT_SUCCESS;
}