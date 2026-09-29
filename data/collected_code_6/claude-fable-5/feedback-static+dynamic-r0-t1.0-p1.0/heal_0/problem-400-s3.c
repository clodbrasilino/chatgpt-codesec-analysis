#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple tuple;
    int count;
} TupleFreq;

static void normalize_tuple(Tuple *t)
{
    if (t->a > t->b) {
        int temp = t->a;
        t->a = t->b;
        t->b = temp;
    }
}

static int tuples_equal(const Tuple *x, const Tuple *y)
{
    return (x->a == y->a) && (x->b == y->b);
}

static TupleFreq *extract_frequency(const Tuple *tuples, size_t n, size_t *out_count)
{
    TupleFreq *freq;
    size_t unique_count = 0;
    size_t i;
    size_t j;

    if (tuples == NULL || out_count == NULL || n == 0) {
        if (out_count != NULL) {
            *out_count = 0;
        }
        return NULL;
    }

    freq = malloc(n * sizeof(TupleFreq));
    if (freq == NULL) {
        *out_count = 0;
        return NULL;
    }

    for (i = 0; i < n; i++) {
        Tuple norm = tuples[i];
        int found = 0;

        normalize_tuple(&norm);

        for (j = 0; j < unique_count; j++) {
            if (tuples_equal(&freq[j].tuple, &norm)) {
                freq[j].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            freq[unique_count].tuple = norm;
            freq[unique_count].count = 1;
            unique_count++;
        }
    }

    *out_count = unique_count;
    return freq;
}

int main(void)
{
    Tuple list[] = {
        {3, 1}, {1, 3}, {2, 5}, {5, 2}, {4, 4}, {2, 5}, {6, 7}
    };
    size_t n = sizeof(list) / sizeof(list[0]);
    size_t unique_count = 0;
    size_t i;
    TupleFreq *result;

    result = extract_frequency(list, n, &unique_count);
    if (result == NULL) {
        fprintf(stderr, "Failed to compute tuple frequencies\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < unique_count; i++) {
        if (printf("(%d, %d): %d\n", result[i].tuple.a, result[i].tuple.b,
                   result[i].count) < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}