#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const int *values;
    size_t length;
} Tuple;

typedef struct {
    int *values;
    size_t length;
    size_t frequency;
} TupleFrequency;

typedef struct {
    int *values;
    size_t length;
} OwnedTuple;

static int compare_ints(const void *left, const void *right)
{
    int a = *(const int *)left;
    int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int compare_owned_tuples(const void *left, const void *right)
{
    const OwnedTuple *a = left;
    const OwnedTuple *b = right;
    size_t minimum = a->length < b->length ? a->length : b->length;

    for (size_t i = 0; i < minimum; ++i) {
        if (a->values[i] != b->values[i]) {
            return (a->values[i] > b->values[i]) -
                   (a->values[i] < b->values[i]);
        }
    }

    return (a->length > b->length) - (a->length < b->length);
}

static void free_owned_tuples(OwnedTuple *tuples, size_t count)
{
    if (tuples == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(tuples[i].values);
    }

    free(tuples);
}

void free_tuple_frequencies(TupleFrequency *frequencies, size_t count)
{
    if (frequencies == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(frequencies[i].values);
    }

    free(frequencies);
}

int extract_tuple_frequencies(const Tuple *tuples,
                              size_t tuple_count,
                              TupleFrequency **output,
                              size_t *output_count)
{
    OwnedTuple *canonical = NULL;
    TupleFrequency *frequencies = NULL;
    size_t unique_count = 0;

    if (output == NULL || output_count == NULL) {
        return EINVAL;
    }

    *output = NULL;
    *output_count = 0;

    if (tuple_count == 0) {
        return 0;
    }

    if (tuples == NULL) {
        return EINVAL;
    }

    if (tuple_count > SIZE_MAX / sizeof(*canonical)) {
        return EOVERFLOW;
    }

    canonical = calloc(tuple_count, sizeof(*canonical));
    if (canonical == NULL) {
        return ENOMEM;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        size_t length = tuples[i].length;

        canonical[i].length = length;

        if (length == 0) {
            continue;
        }

        if (tuples[i].values == NULL) {
            free_owned_tuples(canonical, tuple_count);
            return EINVAL;
        }

        if (length > SIZE_MAX / sizeof(*canonical[i].values)) {
            free_owned_tuples(canonical, tuple_count);
            return EOVERFLOW;
        }

        canonical[i].values = malloc(length * sizeof(*canonical[i].values));
        if (canonical[i].values == NULL) {
            free_owned_tuples(canonical, tuple_count);
            return ENOMEM;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(canonical[i].values,
               tuples[i].values,
               length * sizeof(*canonical[i].values));

        if (length > 1) {
            qsort(canonical[i].values,
                  length,
                  sizeof(*canonical[i].values),
                  compare_ints);
        }
    }

    qsort(canonical,
          tuple_count,
          sizeof(*canonical),
          compare_owned_tuples);

    for (size_t i = 0; i < tuple_count; ++i) {
        if (i == 0 ||
            compare_owned_tuples(&canonical[i - 1], &canonical[i]) != 0) {
            ++unique_count;
        }
    }

    if (unique_count > SIZE_MAX / sizeof(*frequencies)) {
        free_owned_tuples(canonical, tuple_count);
        return EOVERFLOW;
    }

    frequencies = calloc(unique_count, sizeof(*frequencies));
    if (frequencies == NULL) {
        free_owned_tuples(canonical, tuple_count);
        return ENOMEM;
    }

    size_t result_index = 0;
    size_t index = 0;

    while (index < tuple_count) {
        size_t next = index + 1;

        while (next < tuple_count &&
               compare_owned_tuples(&canonical[index],
                                    &canonical[next]) == 0) {
            ++next;
        }

        frequencies[result_index].values = canonical[index].values;
        frequencies[result_index].length = canonical[index].length;
        frequencies[result_index].frequency = next - index;
        canonical[index].values = NULL;

        for (size_t i = index + 1; i < next; ++i) {
            free(canonical[i].values);
            canonical[i].values = NULL;
        }

        ++result_index;
        index = next;
    }

    free(canonical);
    *output = frequencies;
    *output_count = unique_count;

    return 0;
}

static int print_tuple_frequencies(const TupleFrequency *frequencies,
                                   size_t count)
{
    for (size_t i = 0; i < count; ++i) {
        if (printf("(") < 0) {
            return EIO;
        }

        for (size_t j = 0; j < frequencies[i].length; ++j) {
            if (printf("%s%d",
                       j == 0 ? "" : ", ",
                       frequencies[i].values[j]) < 0) {
                return EIO;
            }
        }

        if (printf("): %zu\n", frequencies[i].frequency) < 0) {
            return EIO;
        }
    }

    return ferror(stdout) ? EIO : 0;
}

int main(void)
{
    const int tuple1[] = {1, 2, 3};
    const int tuple2[] = {3, 1, 2};
    const int tuple3[] = {4, 5};
    const int tuple4[] = {5, 4};
    const int tuple5[] = {2, 3, 1};
    const int tuple6[] = {7, 8, 9};

    const Tuple tuples[] = {
        {tuple1, sizeof(tuple1) / sizeof(tuple1[0])},
        {tuple2, sizeof(tuple2) / sizeof(tuple2[0])},
        {tuple3, sizeof(tuple3) / sizeof(tuple3[0])},
        {tuple4, sizeof(tuple4) / sizeof(tuple4[0])},
        {tuple5, sizeof(tuple5) / sizeof(tuple5[0])},
        {tuple6, sizeof(tuple6) / sizeof(tuple6[0])},
        {NULL, 0},
        {NULL, 0}
    };

    TupleFrequency *frequencies = NULL;
    size_t frequency_count = 0;
    int status = extract_tuple_frequencies(
        tuples,
        sizeof(tuples) / sizeof(tuples[0]),
        &frequencies,
        &frequency_count
    );

    if (status != 0) {
        fprintf(stderr, "Failed to extract tuple frequencies: %s\n",
                strerror(status));
        return EXIT_FAILURE;
    }

    status = print_tuple_frequencies(frequencies, frequency_count);
    free_tuple_frequencies(frequencies, frequency_count);

    if (status != 0) {
        fprintf(stderr, "Failed to write output\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}