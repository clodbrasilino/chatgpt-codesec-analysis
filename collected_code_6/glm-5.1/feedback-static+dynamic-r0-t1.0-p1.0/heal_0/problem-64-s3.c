#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a;
    int b;
} Tuple;

void sort_tuples(Tuple *tuples, size_t n, int (*lambda)(const Tuple *, const Tuple *)) {
    if (tuples == NULL || n == 0 || lambda == NULL) {
        return;
    }
    qsort(tuples, n, sizeof(Tuple), lambda);
}

int main(void) {
    Tuple data[] = {{3, 1}, {1, 5}, {2, 2}, {5, 0}};
    size_t n = sizeof(data) / sizeof(data[0]);

    sort_tuples(data, n, NULL);

    int (*cmp_first)(const Tuple *, const Tuple *) = NULL;
    cmp_first = (int (*)(const Tuple *, const Tuple *))lambda(int a, int b) {
        if (a < b) return -1;
        if (a > b) return 1;
        return 0;
    }((const Tuple *x, const Tuple *y) { return (x->a > y->a) - (x->a < y->a); });

    sort_tuples(data, n, cmp_first);

    for (size_t i = 0; i < n; i++) {
        printf("{%d, %d}\n", data[i].a, data[i].b);
    }

    return 0;
}