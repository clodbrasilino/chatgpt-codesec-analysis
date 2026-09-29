#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    
    if (tuple_a->second < tuple_b->second) return -1;
    if (tuple_a->second > tuple_b->second) return 1;
    return 0;
}

void sort_tuples(Tuple *tuples, size_t size) {
    if (tuples == NULL || size == 0) {
        return;
    }
    qsort(tuples, size, sizeof(Tuple), compare_tuples);
}

int main(void) {
    Tuple tuples[] = {
        {1, 5},
        {2, 3},
        {3, 8},
        {4, 1}
    };
    
    size_t size = sizeof(tuples) / sizeof(tuples[0]);
    
    sort_tuples(tuples, size);
    
    for (size_t i = 0; i < size; ++i) {
        printf("(%d, %d)\n", tuples[i].first, tuples[i].second);
    }
    
    return 0;
}