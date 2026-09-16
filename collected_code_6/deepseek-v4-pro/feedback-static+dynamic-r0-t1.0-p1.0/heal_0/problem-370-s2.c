#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float value;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    
    if (tuple_a->value < tuple_b->value) return -1;
    if (tuple_a->value > tuple_b->value) return 1;
    return 0;
}

void sort_tuples(Tuple *tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return;
    }
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
}

int main(void) {
    Tuple tuples[] = {
        {1, 3.14f},
        {2, 1.59f},
        {3, 2.65f},
        {4, 0.98f},
        {5, 5.00f}
    };
    
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    
    sort_tuples(tuples, count);
    
    for (size_t i = 0; i < count; i++) {
        printf("id: %d, value: %.2f\n", tuples[i].id, tuples[i].value);
    }
    
    return 0;
}