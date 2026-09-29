#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Pair;

typedef struct {
    Pair key;
    int count;
} Occurrence;

static void normalize_pair(Pair *p)
{
    if (p->a > p->b) {
        int tmp = p->a;
        p->a = p->b;
        p->b = tmp;
    }
}

static int pairs_equal(const Pair *x, const Pair *y)
{
    return (x->a == y->a) && (x->b == y->b);
}

int check_occurrences(const Pair *tuples, size_t n, Occurrence **result, size_t *result_count)
{
    if (tuples == NULL || result == NULL || result_count == NULL) {
        return -1;
    }

    if (n == 0) {
        *result = NULL;
        *result_count = 0;
        return 0;
    }

    Occurrence *occ = calloc(n, sizeof(Occurrence));
    if (occ == NULL) {
        return -1;
    }

    size_t used = 0;

    for (size_t i = 0; i < n; i++) {
        Pair p = tuples[i];
        normalize_pair(&p);

        size_t j;
        for (j = 0; j < used; j++) {
            if (pairs_equal(&occ[j].key, &p)) {
                occ[j].count++;
                break;
            }
        }

        if (j == used) {
            occ[used].key = p;
            occ[used].count = 1;
            used++;
        }
    }

    *result = occ;
    *result_count = used;
    return 0;
}

int main(void)
{
    Pair tuples[] = { {3, 1}, {1, 3}, {2, 5}, {5, 2}, {6, 3} };
    size_t n = sizeof(tuples) / sizeof(tuples[0]);

    Occurrence *occ = NULL;
    size_t count = 0;

    if (check_occurrences(tuples, n, &occ, &count) != 0) {
        fprintf(stderr, "Error: failed to compute occurrences\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        if (printf("(%d, %d): %d\n", occ[i].key.a, occ[i].key.b, occ[i].count) < 0) {
            free(occ);
            return EXIT_FAILURE;
        }
    }

    free(occ);
    return EXIT_SUCCESS;
}