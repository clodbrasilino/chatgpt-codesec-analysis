#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
    int third;
} Tuple;

int compare_tuples(const void *a, const void *b)
{
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    
    if (tuple_a->third < tuple_b->third) {
        return -1;
    } else if (tuple_a->third > tuple_b->third) {
        return 1;
    } else {
        return 0;
    }
}

int sort_tuples_by_last(Tuple *tuples, size_t count)
{
    if (tuples == NULL || count == 0) {
        return -1;
    }
    
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        {1, 2, 5},
        {3, 4, 2},
        {5, 6, 8},
        {7, 8, 1},
        {9, 10, 3}
    };
    
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    size_t i;
    
    printf("Original list:\n");
    for (i = 0; i < count; i++) {
        printf("(%d, %d, %d)\n", tuples[i].first, tuples[i].second, tuples[i].third);
    }
    
    if (sort_tuples_by_last(tuples, count) != 0) {
        fprintf(stderr, "Error: Failed to sort tuples\n");
        return EXIT_FAILURE;
    }
    
    printf("\nSorted list by last element:\n");
    for (i = 0; i < count; i++) {
        printf("(%d, %d, %d)\n", tuples[i].first, tuples[i].second, tuples[i].third);
    }
    
    return EXIT_SUCCESS;
}