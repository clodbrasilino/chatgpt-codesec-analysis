#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    size_t length;
    int *values;
} Tuple;

typedef struct {
    Tuple tuple;
    size_t frequency;
} TupleFrequency;

static int compare_ints(const void *left, const void *right)
{
    int a = *(const int *)left;
    int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int compare_tuples(const void *left, const void *right)
{
    const Tuple *a = left;
    const Tuple *b = right;
    size_t i;
    size_t limit = a->length < b->length ? a->length : b->length;

    for (i = 0; i < limit; ++i) {
        if (a->values[i] != b->values[i]) {
            return (a->values[i] > b->values[i]) -
                   (a->values[i] < b->values[i]);
        }
    }

    return (a->length > b->length) - (a->length < b->length);
}

static int tuples_equal(const Tuple *a, const Tuple *b)
{
    return compare_tuples(a, b) == 0;
}

static void free_tuples(Tuple *tuples, size_t count)
{
    size_t i;

    if (tuples == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(tuples[i].values);
    }

    free(tuples);
}

void free_tuple_frequencies(TupleFrequency *frequencies, size_t count)
{
    size_t i;

    if (frequencies == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(frequencies[i].tuple.values);
    }

    free(frequencies);
}

int extract_tuple_frequencies(const Tuple *tuples,
                              size_t count,
                              TupleFrequency **output,
                              size_t *output_count)
{
    Tuple *canonical = NULL;
    TupleFrequency *frequencies = NULL;
    size_t i;
    size_t unique_count = 0;

    if (output == NULL || output_count == NULL) {
        return -1;
    }

    *output = NULL;
    *output_count = 0;

    if (count == 0) {
        return 0;
    }

    if (tuples == NULL ||
        count > SIZE_MAX / sizeof(*canonical) ||
        count > SIZE_MAX / sizeof(*frequencies)) {
        return -1;
    }

    canonical = calloc(count, sizeof(*canonical));
    if (canonical == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        canonical[i].length = tuples[i].length;

        if (tuples[i].length == 0) {
            continue;
        }

        if (tuples[i].values == NULL ||
            tuples[i].length > SIZE_MAX / sizeof(*tuples[i].values)) {
            free_tuples(canonical, count);
            return -1;
        }

        canonical[i].values =
            malloc(tuples[i].length * sizeof(*canonical[i].values));

        if (canonical[i].values == NULL) {
            free_tuples(canonical, count);
            return -1;
        }

        for (size_t j = 0; j < tuples[i].length; ++j) {
            canonical[i].values[j] = tuples[i].values[j];
        }

        if (canonical[i].length > 1) {
            qsort(canonical[i].values,
                  canonical[i].length,
                  sizeof(*canonical[i].values),
                  compare_ints);
        }
    }

    qsort(canonical, count, sizeof(*canonical), compare_tuples);

    frequencies = calloc(count, sizeof(*frequencies));
    if (frequencies == NULL) {
        free_tuples(canonical, count);
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (unique_count > 0 &&
            tuples_equal(&canonical[i],
                         &frequencies[unique_count - 1].tuple)) {
            ++frequencies[unique_count - 1].frequency;
            free(canonical[i].values);
            canonical[i].values = NULL;
        } else {
            frequencies[unique_count].tuple = canonical[i];
            frequencies[unique_count].frequency = 1;
            canonical[i].values = NULL;
            ++unique_count;
        }
    }

    free(canonical);
    *output = frequencies;
    *output_count = unique_count;

    return 0;
}

int main(void)
{
    Tuple *tuples = NULL;
    TupleFrequency *frequencies = NULL;
    size_t tuple_count;
    size_t tuple_length;
    size_t frequency_count = 0;
    size_t i;
    size_t j;
    int status = EXIT_FAILURE;

    if (scanf("%zu %zu", &tuple_count, &tuple_length) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (tuple_count > SIZE_MAX / sizeof(*tuples) ||
        tuple_length > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Input size is too large\n");
        return EXIT_FAILURE;
    }

    if (tuple_count > 0) {
        tuples = calloc(tuple_count, sizeof(*tuples));
        if (tuples == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < tuple_count; ++i) {
        tuples[i].length = tuple_length;

        if (tuple_length > 0) {
            tuples[i].values =
                malloc(tuple_length * sizeof(*tuples[i].values));

            if (tuples[i].values == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                goto cleanup;
            }
        }

        for (j = 0; j < tuple_length; ++j) {
            if (scanf("%d", &tuples[i].values[j]) != 1) {
                fprintf(stderr, "Invalid tuple data\n");
                goto cleanup;
            }
        }
    }

    if (extract_tuple_frequencies(tuples,
                                  tuple_count,
                                  &frequencies,
                                  &frequency_count) != 0) {
        fprintf(stderr, "Unable to extract tuple frequencies\n");
        goto cleanup;
    }

    for (i = 0; i < frequency_count; ++i) {
        if (putchar('(') == EOF) {
            goto cleanup;
        }

        for (j = 0; j < frequencies[i].tuple.length; ++j) {
            if (j > 0 && printf(", ") < 0) {
                goto cleanup;
            }

            if (printf("%d", frequencies[i].tuple.values[j]) < 0) {
                goto cleanup;
            }
        }

        if (printf("): %zu\n", frequencies[i].frequency) < 0) {
            goto cleanup;
        }
    }

    if (fflush(stdout) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free_tuple_frequencies(frequencies, frequency_count);
    free_tuples(tuples, tuple_count);
    return status;
}