#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a;
    int b;
} Tuple;

void sort_tuples(Tuple *tuples, size_t n, int (*lambda)(const void *, const void *)) {
    if (tuples == NULL || n == 0 || lambda == NULL) {
        return;
    }
    qsort(tuples, n, sizeof(Tuple), lambda);
}

int cmp_first(const void *p1, const void *p2) {
    const Tuple *x = (const Tuple *)p1;
    const Tuple *y = (const Tuple *)p2;
    return (x->a > y->a) - (x->a < y->a);
}

int main(void) {
    Tuple data[] = {{3, 1}, {1, 5}, {2, 2}, {5, 0}};
    size_t n = sizeof(data) / sizeof(data[0]);

    sort_tuples(data, n, NULL);

    int (*cmp_first_ptr)(const void *, const void *) = cmp_first;

    sort_tuples(data, n, cmp_first_ptr);

    for (size_t i = 0; i < n; i++) {
        printf("{%d, %d}\n", data[i].a, data[i].b);
    }

    return 0;
}