#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
    size_t original_index;
} Tuple;

typedef struct {
    int value;
    size_t count;
} Frequency;

static int compare_frequency_values(const void *left, const void *right)
{
    const Frequency *a = left;
    const Frequency *b = right;

    return (a->value > b->value) - (a->value < b->value);
}

static size_t find_frequency(const Frequency *frequencies, size_t count, int value)
{
    size_t low = 0;
    size_t high = count;

    while (low < high) {
        size_t middle = low + (high - low) / 2;

        if (frequencies[middle].value < value) {
            low = middle + 1;
        } else {
            high = middle;
        }
    }

    return frequencies[low].count;
}

static const Frequency *sort_frequencies;
static size_t sort_frequency_count;

static int compare_tuples(const void *left, const void *right)
{
    const Tuple *a = left;
    const Tuple *b = right;
    size_t a_count = find_frequency(sort_frequencies, sort_frequency_count, a->first);
    size_t b_count = find_frequency(sort_frequencies, sort_frequency_count, b->first);

    if (a_count != b_count) {
        return a_count < b_count ? 1 : -1;
    }

    return (a->original_index > b->original_index) -
           (a->original_index < b->original_index);
}

static int sort_by_first_occurrence(Tuple *tuples, size_t count)
{
    Frequency *frequencies;
    size_t unique_count;

    if (tuples == NULL && count != 0) {
        return -1;
    }

    if (count < 2) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*frequencies)) {
        return -1;
    }

    frequencies = malloc(count * sizeof(*frequencies));
    if (frequencies == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        frequencies[i].value = tuples[i].first;
        frequencies[i].count = 1;
        tuples[i].original_index = i;
    }

    qsort(frequencies, count, sizeof(*frequencies), compare_frequency_values);

    unique_count = 0;
    for (size_t i = 0; i < count; ++i) {
        if (unique_count > 0 &&
            frequencies[unique_count - 1].value == frequencies[i].value) {
            ++frequencies[unique_count - 1].count;
        } else {
            frequencies[unique_count++] = frequencies[i];
        }
    }

    sort_frequencies = frequencies;
    sort_frequency_count = unique_count;
    qsort(tuples, count, sizeof(*tuples), compare_tuples);
    sort_frequencies = NULL;
    sort_frequency_count = 0;

    free(frequencies);
    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        {2, 10, 0},
        {1, 20, 0},
        {2, 30, 0},
        {3, 40, 0},
        {1, 50, 0},
        {2, 60, 0}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    if (sort_by_first_occurrence(tuples, count) != 0) {
        fputs("Unable to sort tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("(%d, %d)\n", tuples[i].first, tuples[i].second) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}