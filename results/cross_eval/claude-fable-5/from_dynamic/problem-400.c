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

static Tuple normalize_tuple(Tuple t)
{
    Tuple result;

    if (t.a <= t.b) {
        result.a = t.a;
        result.b = t.b;
    } else {
        result.a = t.b;
        result.b = t.a;
    }
    return result;
}

static int tuples_equal(Tuple x, Tuple y)
{
    return (x.a == y.a) && (x.b == y.b);
}

static int extract_frequency(const Tuple *list, size_t n, TupleFreq **out_freqs, size_t *out_count)
{
    TupleFreq *freqs;
    size_t unique_count;
    size_t i;
    size_t j;

    if ((out_freqs == NULL) || (out_count == NULL)) {
        return -1;
    }

    *out_freqs = NULL;
    *out_count = 0U;

    if ((list == NULL) || (n == 0U)) {
        return 0;
    }

    freqs = malloc(n * sizeof(*freqs));
    if (freqs == NULL) {
        return -1;
    }

    unique_count = 0U;

    for (i = 0U; i < n; i++) {
        Tuple norm = normalize_tuple(list[i]);
        int found = 0;

        for (j = 0U; j < unique_count; j++) {
            if (tuples_equal(freqs[j].tuple, norm)) {
                freqs[j].count++;
                found = 1;
                break;
            }
        }

        if (found == 0) {
            freqs[unique_count].tuple = norm;
            freqs[unique_count].count = 1;
            unique_count++;
        }
    }

    *out_freqs = freqs;
    *out_count = unique_count;
    return 0;
}

int main(void)
{
    Tuple list[] = {
        {3, 5}, {5, 3}, {1, 2}, {2, 1}, {3, 5}, {4, 6}, {6, 4}, {1, 2}
    };
    size_t n = sizeof(list) / sizeof(list[0]);
    TupleFreq *freqs = NULL;
    size_t count = 0U;
    size_t i;

    if (extract_frequency(list, n, &freqs, &count) != 0) {
        fprintf(stderr, "Failed to compute tuple frequencies\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; i++) {
        if (printf("(%d, %d): %d\n", freqs[i].tuple.a, freqs[i].tuple.b, freqs[i].count) < 0) {
            free(freqs);
            return EXIT_FAILURE;
        }
    }

    free(freqs);
    return EXIT_SUCCESS;
}