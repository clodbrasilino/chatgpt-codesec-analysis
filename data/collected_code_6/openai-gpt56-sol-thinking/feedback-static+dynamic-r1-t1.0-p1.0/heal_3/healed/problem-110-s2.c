#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int64_t start;
    int64_t end;
} Range;

static int compare_int64(const void *left, const void *right)
{
    const int64_t a = *(const int64_t *)left;
    const int64_t b = *(const int64_t *)right;

    return (a > b) - (a < b);
}

static int extract_missing_ranges(const int64_t *values,
                                  size_t count,
                                  int64_t range_start,
                                  int64_t range_end,
                                  Range **missing_ranges,
                                  size_t *missing_count)
{
    int64_t *sorted = NULL;
    Range *ranges = NULL;
    size_t range_capacity;
    size_t result_count = 0;
    int64_t current;
    int completed = 0;

    if (missing_ranges == NULL || missing_count == NULL) {
        return EINVAL;
    }

    *missing_ranges = NULL;
    *missing_count = 0;

    if ((count != 0 && values == NULL) || range_start > range_end) {
        return EINVAL;
    }

    if (count > SIZE_MAX / sizeof(*sorted) || count == SIZE_MAX) {
        return EOVERFLOW;
    }

    range_capacity = count + 1;

    if (range_capacity > SIZE_MAX / sizeof(*ranges)) {
        return EOVERFLOW;
    }

    if (count != 0) {
        sorted = malloc(count * sizeof(*sorted));
        if (sorted == NULL) {
            return ENOMEM;
        }

        for (size_t i = 0; i < count; ++i) {
            sorted[i] = values[i];
        }

        if (count > 1) {
            qsort(sorted, count, sizeof(*sorted), compare_int64);
        }
    }

    ranges = malloc(range_capacity * sizeof(*ranges));
    if (ranges == NULL) {
        free(sorted);
        return ENOMEM;
    }

    current = range_start;

    for (size_t i = 0; i < count; ++i) {
        const int64_t value = sorted[i];

        if (value < range_start) {
            continue;
        }

        if (value > range_end) {
            break;
        }

        if (value < current) {
            continue;
        }

        if (value > current) {
            ranges[result_count].start = current;
            ranges[result_count].end = value - 1;
            ++result_count;
        }

        if (value == range_end) {
            completed = 1;
            break;
        }

        current = value + 1;
    }

    if (!completed && current <= range_end) {
        ranges[result_count].start = current;
        ranges[result_count].end = range_end;
        ++result_count;
    }

    free(sorted);

    if (result_count == 0) {
        free(ranges);
        ranges = NULL;
    }

    *missing_ranges = ranges;
    *missing_count = result_count;

    return 0;
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end = NULL;
    intmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0') {
        return EINVAL;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || parsed < INT64_MIN || parsed > INT64_MAX) {
        return ERANGE;
    }

    if (end == text || *end != '\0') {
        return EINVAL;
    }

    *value = (int64_t)parsed;
    return 0;
}

int main(int argc, char **argv)
{
    int64_t range_start;
    int64_t range_end;
    int64_t *values = NULL;
    Range *missing_ranges = NULL;
    size_t value_count;
    size_t missing_count = 0;
    int status;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s start end [values ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    status = parse_int64(argv[1], &range_start);
    if (status != 0) {
        fprintf(stderr, "Invalid start value: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    status = parse_int64(argv[2], &range_end);
    if (status != 0) {
        fprintf(stderr, "Invalid end value: %s\n", argv[2]);
        return EXIT_FAILURE;
    }

    value_count = (size_t)(argc - 3);

    if (value_count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Too many values\n");
        return EXIT_FAILURE;
    }

    if (value_count != 0) {
        values = malloc(value_count * sizeof(*values));
        if (values == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < value_count; ++i) {
        status = parse_int64(argv[i + 3], &values[i]);
        if (status != 0) {
            fprintf(stderr, "Invalid list value: %s\n", argv[i + 3]);
            free(values);
            return EXIT_FAILURE;
        }
    }

    status = extract_missing_ranges(values,
                                    value_count,
                                    range_start,
                                    range_end,
                                    &missing_ranges,
                                    &missing_count);

    free(values);

    if (status != 0) {
        fprintf(stderr,
                "Unable to extract missing ranges: %s\n",
                strerror(status));
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < missing_count; ++i) {
        if (printf("[%" PRId64 ", %" PRId64 "]\n",
                   missing_ranges[i].start,
                   missing_ranges[i].end) < 0) {
            free(missing_ranges);
            return EXIT_FAILURE;
        }
    }

    free(missing_ranges);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}