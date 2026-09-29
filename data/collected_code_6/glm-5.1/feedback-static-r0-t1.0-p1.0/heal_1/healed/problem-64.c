#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef int (*Comparator)(const void *, const void *);

void sort_tuples(Tuple *arr, size_t n, Comparator cmp) {
    if (arr == NULL || n == 0 || cmp == NULL) {
        return;
    }
    qsort(arr, n, sizeof(Tuple), cmp);
}

int tuple_compare(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    if (ta->first != tb->first) {
        return ta->first - tb->first;
    }
    return ta->second - tb->second;
}

int main(void) {
    Tuple arr[] = {
        {5, 2},
        {1, 9},
        {3, 4},
        {1, 1}
    };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    Comparator cmp = tuple_compare;
    sort_tuples(arr, n, cmp);
    for (size_t i = 0; i < n; i++) {
        printf("(%d, %d)\n", arr[i].first, arr[i].second);
    }
    return 0;
}