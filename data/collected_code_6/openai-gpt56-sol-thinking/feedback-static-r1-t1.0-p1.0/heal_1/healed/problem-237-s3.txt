#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t occurrences;
} RecordOccurrence;

typedef struct {
    size_t occurrences;
    size_t index;
} FrequencyReference;

typedef enum {
    CHECK_OK,
    CHECK_INVALID_ARGUMENT,
    CHECK_SIZE_ERROR,
    CHECK_NO_MEMORY
} CheckStatus;

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int compare_frequencies(const void *left, const void *right)
{
    const FrequencyReference *a = left;
    const FrequencyReference *b = right;

    if (a->occurrences < b->occurrences) {
        return -1;
    }

    if (a->occurrences > b->occurrences) {
        return 1;
    }

    return (a->index > b->index) - (a->index < b->index);
}

static CheckStatus check_similar_occurrences(
    const int *tuple,
    size_t tuple_size,
    RecordOccurrence **matches,
    size_t *match_count)
{
    int *sorted_values = NULL;
    RecordOccurrence *occurrences = NULL;
    FrequencyReference *frequencies = NULL;
    bool *selected = NULL;
    RecordOccurrence *result = NULL;
    size_t unique_count = 0;
    size_t result_count = 0;
    size_t i = 0;

    if (matches == NULL || match_count == NULL) {
        return CHECK_INVALID_ARGUMENT;
    }

    *matches = NULL;
    *match_count = 0;

    if (tuple_size == 0) {
        return CHECK_OK;
    }

    if (tuple == NULL) {
        return CHECK_INVALID_ARGUMENT;
    }

    if (tuple_size > SIZE_MAX / sizeof(*sorted_values) ||
        tuple_size > SIZE_MAX / sizeof(*occurrences) ||
        tuple_size > SIZE_MAX / sizeof(*frequencies) ||
        tuple_size > SIZE_MAX / sizeof(*selected)) {
        return CHECK_SIZE_ERROR;
    }

    sorted_values = malloc(tuple_size * sizeof(*sorted_values));
    occurrences = malloc(tuple_size * sizeof(*occurrences));
    frequencies = malloc(tuple_size * sizeof(*frequencies));
    selected = calloc(tuple_size, sizeof(*selected));

    if (sorted_values == NULL ||
        occurrences == NULL ||
        frequencies == NULL ||
        selected == NULL) {
        free(sorted_values);
        free(occurrences);
        free(frequencies);
        free(selected);
        return CHECK_NO_MEMORY;
    }

    for (i = 0; i < tuple_size; ++i) {
        sorted_values[i] = tuple[i];
    }

    qsort(sorted_values, tuple_size, sizeof(*sorted_values), compare_ints);

    i = 0;
    while (i < tuple_size) {
        size_t end = i + 1;

        while (end < tuple_size && sorted_values[end] == sorted_values[i]) {
            ++end;
        }

        occurrences[unique_count].value = sorted_values[i];
        occurrences[unique_count].occurrences = end - i;
        frequencies[unique_count].occurrences = end - i;
        frequencies[unique_count].index = unique_count;

        ++unique_count;
        i = end;
    }

    qsort(
        frequencies,
        unique_count,
        sizeof(*frequencies),
        compare_frequencies
    );

    i = 0;
    while (i < unique_count) {
        size_t end = i + 1;

        while (end < unique_count &&
               frequencies[end].occurrences ==
                   frequencies[i].occurrences) {
            ++end;
        }

        if (end - i > 1) {
            for (size_t j = i; j < end; ++j) {
                selected[frequencies[j].index] = true;
            }
        }

        i = end;
    }

    for (i = 0; i < unique_count; ++i) {
        if (selected[i]) {
            ++result_count;
        }
    }

    if (result_count > 0) {
        result = malloc(result_count * sizeof(*result));

        if (result == NULL) {
            free(sorted_values);
            free(occurrences);
            free(frequencies);
            free(selected);
            return CHECK_NO_MEMORY;
        }

        result_count = 0;

        for (i = 0; i < unique_count; ++i) {
            if (selected[i]) {
                result[result_count++] = occurrences[i];
            }
        }
    }

    free(sorted_values);
    free(occurrences);
    free(frequencies);
    free(selected);

    *matches = result;
    *match_count = result_count;

    return CHECK_OK;
}

int main(void)
{
    size_t tuple_size = 0;
    int *tuple = NULL;
    RecordOccurrence *matches = NULL;
    size_t match_count = 0;
    CheckStatus status;

    if (scanf("%zu", &tuple_size) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (tuple_size > SIZE_MAX / sizeof(*tuple)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (tuple_size > 0) {
        tuple = malloc(tuple_size * sizeof(*tuple));

        if (tuple == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < tuple_size; ++i) {
        if (scanf("%d", &tuple[i]) != 1) {
            free(tuple);
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    status = check_similar_occurrences(
        tuple,
        tuple_size,
        &matches,
        &match_count
    );

    free(tuple);

    if (status != CHECK_OK) {
        free(matches);
        fputs("Unable to check occurrences\n", stderr);
        return EXIT_FAILURE;
    }

    if (match_count == 0) {
        if (puts("No records have equal occurrence counts") == EOF) {
            free(matches);
            return EXIT_FAILURE;
        }
    } else {
        for (size_t i = 0; i < match_count; ++i) {
            if (printf(
                    "%d %zu\n",
                    matches[i].value,
                    matches[i].occurrences
                ) < 0) {
                free(matches);
                return EXIT_FAILURE;
            }
        }
    }

    free(matches);
    return EXIT_SUCCESS;
}