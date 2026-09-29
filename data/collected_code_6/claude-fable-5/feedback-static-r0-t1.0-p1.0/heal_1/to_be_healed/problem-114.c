#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TUPLE_SIZE 3

typedef struct {
    int values[TUPLE_SIZE];
} Tuple;

typedef struct {
    Tuple tuple;
    int frequency;
} TupleFreq;

static int tuples_equal(const Tuple *a, const Tuple *b)
{
    return memcmp(a->values, b->values, sizeof(a->values)) == 0;
}

static int assign_frequency(const Tuple *tuples, size_t count, TupleFreq **result, size_t *result_count)
{
    TupleFreq *freqs;
    size_t unique_count;
    size_t i;
    size_t j;
    /* Possible weaknesses found:
     *  The scope of the variable 'found' can be reduced. [variableScope]
     */
    int found;

    if (tuples == NULL || result == NULL || result_count == NULL) {
        return -1;
    }

    if (count == 0) {
        *result = NULL;
        *result_count = 0;
        return 0;
    }

    freqs = calloc(count, sizeof(TupleFreq));
    if (freqs == NULL) {
        return -1;
    }

    unique_count = 0;
    for (i = 0; i < count; i++) {
        found = 0;
        for (j = 0; j < unique_count; j++) {
            if (tuples_equal(&tuples[i], &freqs[j].tuple)) {
                freqs[j].frequency++;
                found = 1;
                break;
            }
        }
        if (!found) {
            freqs[unique_count].tuple = tuples[i];
            freqs[unique_count].frequency = 1;
            unique_count++;
        }
    }

    *result = freqs;
    *result_count = unique_count;
    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        { {1, 2, 3} },
        { {4, 5, 6} },
        { {1, 2, 3} },
        { {7, 8, 9} },
        { {4, 5, 6} },
        { {1, 2, 3} }
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    TupleFreq *result = NULL;
    size_t result_count = 0;
    size_t i;
    size_t k;

    if (assign_frequency(tuples, count, &result, &result_count) != 0) {
        fprintf(stderr, "Failed to assign frequencies\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_count; i++) {
        printf("(");
        for (k = 0; k < TUPLE_SIZE; k++) {
            printf("%d", result[i].tuple.values[k]);
            if (k < TUPLE_SIZE - 1) {
                printf(", ");
            }
        }
        printf(") : %d\n", result[i].frequency);
    }

    free(result);
    return EXIT_SUCCESS;
}