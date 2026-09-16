#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    
    if (tuple_a->first < tuple_b->first) {
        return -1;
    } else if (tuple_a->first > tuple_b->first) {
        return 1;
    }
    return 0;
}

int sort_tuples_by_first(Tuple *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return -1;
    }
    qsort(arr, n, sizeof(Tuple), compare_tuples);
    return 0;
}

int main(void) {
    Tuple data[] = {
        {5, 20},
        {2, 10},
        {8, 30},
        {1, 40},
        {5, 50}
    };
    size_t size = sizeof(data) / sizeof(data[0]);
    
    if (sort_tuples_by_first(data, size) != 0) {
        fprintf(stderr, "Error: Invalid input parameters\n");
        return EXIT_FAILURE;
    }
    
    printf("Sorted tuples by first element:\n");
    for (size_t i = 0; i < size; i++) {
        printf("(%d, %d)\n", data[i].first, data[i].second);
    }
    
    return EXIT_SUCCESS;
}