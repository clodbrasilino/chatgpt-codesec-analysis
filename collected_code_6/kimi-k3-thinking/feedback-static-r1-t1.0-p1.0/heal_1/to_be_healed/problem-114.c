#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple tuple;
    size_t frequency;
} TupleFrequency;

static int tuples_equal(Tuple a, Tuple b)
{
    return (a.first == b.first) && (a.second == b.second);
}

size_t assign_frequencies(const Tuple *tuples, size_t count, TupleFrequency **result)
{
    TupleFrequency *frequencies;
    size_t unique_count = 0;
    size_t i;
    size_t j;

    if (result == NULL) {
        return 0;
    }
    *result = NULL;

    if (tuples == NULL || count == 0) {
        return 0;
    }

    frequencies = (TupleFrequency *)calloc(count, sizeof(TupleFrequency));
    if (frequencies == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        int found = 0;
        for (j = 0; j < unique_count; j++) {
            if (tuples_equal(frequencies[j].tuple, tuples[i])) {
                frequencies[j].frequency++;
                found = 1;
                break;
            }
        }
        if (!found) {
            frequencies[unique_count].tuple = tuples[i];
            frequencies[unique_count].frequency = 1;
            unique_count++;
        }
    }

    *result = frequencies;
    return unique_count;
}

int main(void)
{
    Tuple tuples[] = {
        {1, 2}, {3, 4}, {1, 2}, {5, 6}, {3, 4}, {1, 2}, {5, 6}
    };
    /* Possible weaknesses found:
     *  Assignment 'count=sizeof(tuples)/sizeof(tuples[0])', assigned value is 7
     */
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    TupleFrequency *result = NULL;
    size_t unique_count;
    size_t i;

    unique_count = assign_frequencies(tuples, count, &result);
    /* Possible weaknesses found:
     *  Condition 'count>0' is always true [knownConditionTrueFalse]
     *  Condition 'count>0' is always true
     */
    if (result == NULL && count > 0) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < unique_count; i++) {
        printf("(%d, %d) : %zu\n",
               result[i].tuple.first,
               result[i].tuple.second,
               result[i].frequency);
    }

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}