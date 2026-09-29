#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple tuple;
    size_t count;
} TupleFrequency;

static Tuple normalize_tuple(Tuple t)
{
    if (t.first > t.second) {
        int temp = t.first;
        t.first = t.second;
        t.second = temp;
    }
    return t;
}

static int compare_tuples(const void *a, const void *b)
{
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;

    if (ta->first != tb->first) {
        return (ta->first < tb->first) ? -1 : 1;
    }
    if (ta->second != tb->second) {
        return (ta->second < tb->second) ? -1 : 1;
    }
    return 0;
}

static size_t extract_tuple_frequencies(const Tuple *tuples, size_t count,
                                        TupleFrequency **frequencies)
{
    Tuple *normalized;
    size_t unique_count;
    size_t index;
    size_t i;

    if (frequencies == NULL) {
        return 0;
    }
    *frequencies = NULL;

    if (tuples == NULL || count == 0) {
        return 0;
    }

    normalized = (Tuple *)malloc(count * sizeof(*normalized));
    if (normalized == NULL) {
        return 0;
    }

    for (i = 0; i < count; ++i) {
        normalized[i] = normalize_tuple(tuples[i]);
    }

    qsort(normalized, count, sizeof(*normalized), compare_tuples);

    unique_count = 1;
    for (i = 1; i < count; ++i) {
        if (compare_tuples(&normalized[i], &normalized[i - 1]) != 0) {
            ++unique_count;
        }
    }

    *frequencies = (TupleFrequency *)malloc(unique_count * sizeof(**frequencies));
    if (*frequencies == NULL) {
        free(normalized);
        normalized = NULL;
        return 0;
    }

    index = 0;
    (*frequencies)[0].tuple = normalized[0];
    (*frequencies)[0].count = 1;

    for (i = 1; i < count; ++i) {
        if (compare_tuples(&normalized[i], &(*frequencies)[index].tuple) == 0) {
            ++(*frequencies)[index].count;
        } else {
            ++index;
            (*frequencies)[index].tuple = normalized[i];
            (*frequencies)[index].count = 1;
        }
    }

    free(normalized);
    normalized = NULL;

    return unique_count;
}

int main(void)
{
    Tuple tuples[] = {
        {1, 2}, {2, 1}, {3, 4}, {1, 2}, {4, 3}, {5, 6}, {2, 1}
    };
    /* Possible weaknesses found:
     *  Assignment 'count=sizeof(tuples)/sizeof(tuples[0])', assigned value is 7
     */
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    TupleFrequency *frequencies = NULL;
    size_t unique_count;
    size_t i;

    unique_count = extract_tuple_frequencies(tuples, count, &frequencies);
    /* Possible weaknesses found:
     *  Condition 'count!=0' is always true [knownConditionTrueFalse]
     *  Condition 'count!=0' is always true
     */
    if (frequencies == NULL && count != 0) {
        fprintf(stderr, "Error: unable to compute tuple frequencies\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < unique_count; ++i) {
        printf("(%d, %d) : %zu\n", frequencies[i].tuple.first,
               frequencies[i].tuple.second, frequencies[i].count);
    }

    free(frequencies);
    frequencies = NULL;

    return EXIT_SUCCESS;
}