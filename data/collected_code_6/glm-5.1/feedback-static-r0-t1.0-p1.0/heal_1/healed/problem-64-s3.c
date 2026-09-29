#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a;
    int b;
} Tuple;

int compare_first(const void *p, const void *q) {
    const Tuple *x = p;
    const Tuple *y = q;
    return (x->a > y->a) - (x->a < y->a);
}

void sort_tuples(Tuple *tuples, size_t n, int (*cmp)(const void *, const void *)) {
    if (tuples == NULL || n == 0 || cmp == NULL) {
        return;
    }
    qsort(tuples, n, sizeof(Tuple), cmp);
}

int main(void) {
    Tuple data[] = {{3, 1}, {1, 5}, {2, 2}, {5, 0}};
    size_t n = sizeof(data) / sizeof(data[0]);

    sort_tuples(data, n, compare_first);

    for (size_t i = 0; i < n; i++) {
        printf("{%d, %d}\n", data[i].a, data[i].b);
    }

    return 0;
}