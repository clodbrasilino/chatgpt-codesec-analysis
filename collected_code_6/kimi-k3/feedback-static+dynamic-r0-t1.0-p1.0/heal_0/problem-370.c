#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[32];
    float value;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    
    if (ta->value < tb->value) return -1;
    if (ta->value > tb->value) return 1;
    return 0;
}

int sort_tuples_by_float(Tuple *arr, size_t count) {
    if (arr == NULL || count == 0) {
        return -1;
    }
    qsort(arr, count, sizeof(Tuple), compare_tuples);
    return 0;
}

int main(void) {
    Tuple data[] = {
        {1, "alpha", 3.14f},
        {2, "beta", 1.41f},
        {3, "gamma", 2.72f},
        {4, "delta", 0.58f}
    };
    size_t count = sizeof(data) / sizeof(data[0]);
    
    if (sort_tuples_by_float(data, count) != 0) {
        fprintf(stderr, "Error: Invalid input to sort function\n");
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < count; i++) {
        printf("ID: %d, Name: %s, Value: %.2f\n", 
               data[i].id, data[i].name, (double)data[i].value);
    }
    
    return EXIT_SUCCESS;
}