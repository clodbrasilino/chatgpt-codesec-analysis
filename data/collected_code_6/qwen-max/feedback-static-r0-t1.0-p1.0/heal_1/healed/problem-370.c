#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float value;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *tupleA = (const Tuple *)a;
    const Tuple *tupleB = (const Tuple *)b;
    if (tupleA->value < tupleB->value) return -1;
    if (tupleA->value > tupleB->value) return 1;
    return 0;
}

void sort_tuples(Tuple *array, size_t count) {
    qsort(array, count, sizeof(Tuple), compare_tuples);
}

int main() {
    Tuple array[] = {{1, 3.5f}, {2, 1.2f}, {3, 4.8f}};
    size_t count = sizeof(array) / sizeof(array[0]);
    
    sort_tuples(array, count);

    for (size_t i = 0; i < count; ++i) {
        printf("ID: %d, Value: %.1f\n", array[i].id, array[i].value);
    }
    
    return 0;
}