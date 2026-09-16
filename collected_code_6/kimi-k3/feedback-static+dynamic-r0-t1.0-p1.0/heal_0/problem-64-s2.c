#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
} Tuple;

typedef int (*CompareFunc)(const void *, const void *);

int compare_tuples(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    
    if (ta->x != tb->x) {
        return ta->x - tb->x;
    }
    return ta->y - tb->y;
}

void sort_tuples(Tuple *arr, size_t size, CompareFunc cmp) {
    if (arr != NULL && size > 0 && cmp != NULL) {
        qsort(arr, size, sizeof(Tuple), cmp);
    }
}

int main(void) {
    Tuple tuples[] = {{3, 2}, {1, 5}, {2, 1}, {1, 3}, {3, 1}};
    size_t size = sizeof(tuples) / sizeof(tuples[0]);
    
    sort_tuples(tuples, size, compare_tuples);
    
    for (size_t i = 0; i < size; i++) {
        printf("(%d, %d)\n", tuples[i].x, tuples[i].y);
    }
    
    return 0;
}