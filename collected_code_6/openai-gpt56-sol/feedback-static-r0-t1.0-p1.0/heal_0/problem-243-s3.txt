#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct {
    int first;
    int second;
    size_t original_index;
} Tuple;

typedef struct {
    int value;
    size_t count;
} Frequency;

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static size_t count_value(const int *values, size_t length, int target)
{
    size_t left = 0;
    size_t right = length;

    while (left < right) {
        size_t middle = left + (right - left) / 2;

        if (values[middle] < target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    size_t first = left;
    right = length;

    while (left < right) {
        size_t middle = left + (right - left) / 2;

        if (values[middle] <= target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    return left - first;
}

static size_t find_frequency(const Frequency *frequencies, size_t length, int value)
{
    size_t left = 0;
    size_t right = length;

    while (left < right) {
        size_t middle = left + (right - left) / 2;

        if (frequencies[middle].value < value) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    return frequencies[left].count;
}

static const Frequency *sort_frequencies;
static size_t sort_frequency_count;

static int compare_tuples(const void *lhs, const void *rhs)
{
    const Tuple *a = lhs;
    const Tuple *b = rhs;
    size_t count_a = find_frequency(sort_frequencies, sort_frequency_count, a->first);
    size_t count_b = find_frequency(sort_frequencies, sort_frequency_count, b->first);

    if (count_a != count_b) {
        return count_a < count_b ? 1 : -1;
    }

    if (a->first != b->first) {
        return (a->first > b->first) - (a->first < b->first);
    }

    return (a->original_index > b->original_index) -
           (a->original_index < b->original_index);
}

static int sort_by_first_occurrence(Tuple *tuples, size_t count)
{
    int *values = NULL;
    Frequency *frequencies = NULL;
    size_t unique_count = 0;

    if (tuples == NULL && count != 0) {
        return 0;
    }

    if (count < 2) {
        return 1;
    }

    if (count > SIZE_MAX / sizeof(*values) ||
        count > SIZE_MAX / sizeof(*frequencies)) {
        return 0;
    }

    values = malloc(count * sizeof(*values));
    frequencies = malloc(count * sizeof(*frequencies));

    if (values == NULL || frequencies == NULL) {
        free(values);
        free(frequencies);
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        values[i] = tuples[i].first;
        tuples[i].original_index = i;
    }

    qsort(values, count, sizeof(*values), compare_ints);

    for (size_t i = 0; i < count;) {
        int value = values[i];
        size_t occurrences = count_value(values, count, value);

        frequencies[unique_count].value = value;
        frequencies[unique_count].count = occurrences;
        ++unique_count;
        i += occurrences;
    }

    sort_frequencies = frequencies;
    sort_frequency_count = unique_count;
    qsort(tuples, count, sizeof(*tuples), compare_tuples);
    sort_frequencies = NULL;
    sort_frequency_count = 0;

    free(values);
    free(frequencies);
    return 1;
}

int main(void)
{
    Tuple tuples[] = {
        {3, 10, 0},
        {1, 20, 0},
        {2, 30, 0},
        {3, 40, 0},
        {2, 50, 0},
        {3, 60, 0}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    if (!sort_by_first_occurrence(tuples, count)) {
        fputs("Failed to sort tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("(%d, %d)%c",
                   tuples[i].first,
                   tuples[i].second,
                   i + 1 == count ? '\n' : ' ') < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}