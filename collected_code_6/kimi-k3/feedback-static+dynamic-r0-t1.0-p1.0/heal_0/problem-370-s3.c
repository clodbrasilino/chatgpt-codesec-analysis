#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float value;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    
    if (tuple_a->value < tuple_b->value) {
        return -1;
    }
    if (tuple_a->value > tuple_b->value) {
        return 1;
    }
    return 0;
}

int sort_tuples_by_float(Tuple *array, size_t count) {
    if (array == NULL || count == 0) {
        return -1;
    }
    qsort(array, count, sizeof(Tuple), compare_tuples);
    return 0;
}

int main(void) {
    Tuple data[] = {
        {1, 3.14f},
        {2, 1.59f},
        {3, 2.65f},
        {4, 0.58f}
    };
    size_t count = sizeof(data) / sizeof(data[0]);
    size_t i;
    
    printf("Original:\n");
    for (i = 0; i < count; i++) {
        printf("ID: %d, Value: %.2f\n", data[i].id, data[i].value);
    }
    
    if (sort_tuples_by_float(data, count) != 0) {
        fprintf(stderr, "Error: Invalid parameters for sorting\n");
        return EXIT_FAILURE;
    }
    
    printf("\nSorted by float value:\n");
    for (i = 0; i < count; i++) {
        printf("ID: %d, Value: %.2f\n", data[i].id, data[i].value);
    }
    
    return EXIT_SUCCESS;
}