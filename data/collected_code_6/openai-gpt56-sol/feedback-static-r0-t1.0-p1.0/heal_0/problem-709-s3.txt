#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *key;
    const char *value;
} Tuple;

typedef struct {
    const char *value;
    size_t unique_key_count;
} ValueCount;

static int strings_equal(const char *left, const char *right)
{
    if (left == NULL || right == NULL) {
        return left == right;
    }

    while (*left != '\0' && *left == *right) {
        ++left;
        ++right;
    }

    return *left == *right;
}

static int count_unique_keys_by_value(const Tuple *tuples,
                                      size_t tuple_count,
                                      ValueCount **results,
                                      size_t *result_count)
{
    ValueCount *counts = NULL;
    size_t value_count = 0;

    if (results == NULL || result_count == NULL ||
        (tuples == NULL && tuple_count != 0)) {
        return -1;
    }

    *results = NULL;
    *result_count = 0;

    if (tuple_count == 0) {
        return 0;
    }

    if (tuple_count > SIZE_MAX / sizeof(*counts)) {
        return -1;
    }

    counts = calloc(tuple_count, sizeof(*counts));
    if (counts == NULL) {
        return -1;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        size_t value_index = 0;
        int key_seen = 0;

        if (tuples[i].key == NULL || tuples[i].value == NULL) {
            free(counts);
            return -1;
        }

        while (value_index < value_count &&
               !strings_equal(counts[value_index].value, tuples[i].value)) {
            ++value_index;
        }

        if (value_index == value_count) {
            counts[value_count].value = tuples[i].value;
            counts[value_count].unique_key_count = 0;
            ++value_count;
        }

        for (size_t j = 0; j < i; ++j) {
            if (strings_equal(tuples[j].value, tuples[i].value) &&
                strings_equal(tuples[j].key, tuples[i].key)) {
                key_seen = 1;
                break;
            }
        }

        if (!key_seen) {
            ++counts[value_index].unique_key_count;
        }
    }

    if (value_count < tuple_count) {
        ValueCount *resized = realloc(counts, value_count * sizeof(*counts));
        if (resized != NULL) {
            counts = resized;
        }
    }

    *results = counts;
    *result_count = value_count;
    return 0;
}

int main(void)
{
    const Tuple tuples[] = {
        {"alpha", "red"},
        {"beta", "red"},
        {"alpha", "red"},
        {"alpha", "blue"},
        {"gamma", "blue"},
        {"gamma", "green"}
    };
    ValueCount *counts = NULL;
    size_t count = 0;

    if (count_unique_keys_by_value(
            tuples, sizeof(tuples) / sizeof(tuples[0]), &counts, &count) != 0) {
        fputs("Failed to count unique keys.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("%s: %zu\n", counts[i].value,
                   counts[i].unique_key_count) < 0) {
            free(counts);
            return EXIT_FAILURE;
        }
    }

    free(counts);
    return EXIT_SUCCESS;
}