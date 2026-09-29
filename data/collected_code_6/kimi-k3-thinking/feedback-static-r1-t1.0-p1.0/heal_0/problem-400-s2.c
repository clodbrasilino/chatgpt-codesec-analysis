#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple tuple;
    size_t count;
} TupleFreq;

static Tuple normalize_tuple(Tuple t)
{
    Tuple result;
    if (t.first <= t.second) {
        result.first = t.first;
        result.second = t.second;
    } else {
        result.first = t.second;
        result.second = t.first;
    }
    return result;
}

static int tuples_equal(Tuple a, Tuple b)
{
    return a.first == b.first && a.second == b.second;
}

size_t tuple_frequency(const Tuple *tuples, size_t n, TupleFreq **out)
{
    TupleFreq *result = NULL;
    size_t unique_count = 0;
    size_t i;

    if (out == NULL) {
        return 0;
    }
    *out = NULL;

    if (tuples == NULL || n == 0) {
        return 0;
    }

    for (i = 0; i < n; i++) {
        Tuple norm = normalize_tuple(tuples[i]);
        size_t j;
        int found = 0;

        for (j = 0; j < unique_count; j++) {
            if (tuples_equal(result[j].tuple, norm)) {
                result[j].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            TupleFreq *tmp = realloc(result, (unique_count + 1) * sizeof(*tmp));
            if (tmp == NULL) {
                free(result);
                return 0;
            }
            result = tmp;
            result[unique_count].tuple = norm;
            result[unique_count].count = 1;
            unique_count++;
        }
    }

    *out = result;
    return unique_count;
}

int main(void)
{
    Tuple tuples[] = {
        {1, 2}, {2, 1}, {3, 4}, {1, 2}, {4, 3}, {5, 6}
    };
    size_t n = sizeof(tuples) / sizeof(tuples[0]);
    TupleFreq *freqs = NULL;
    size_t unique;
    size_t i;

    unique = tuple_frequency(tuples, n, &freqs);

    for (i = 0; i < unique; i++) {
        printf("(%d, %d): %zu\n",
               freqs[i].tuple.first,
               freqs[i].tuple.second,
               freqs[i].count);
    }

    free(freqs);
    return 0;
}