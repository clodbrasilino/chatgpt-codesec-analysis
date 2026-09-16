#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int key;
    int value;
} Tuple;

int calculate_max_aggregate(Tuple* tuples, size_t size) {
    if (tuples == NULL || size == 0) {
        return INT_MIN;
    }

    int max_aggregate = INT_MIN;
    int current_aggregate = 0;

    for (size_t i = 0; i < size; ++i) {
        current_aggregate += tuples[i].value;
        if (current_aggregate > max_aggregate) {
            max_aggregate = current_aggregate;
        }
    }

    return max_aggregate;
}

int main(void) {
    size_t num_tuples = 5;
    Tuple* tuple_list = (Tuple*)malloc(num_tuples * sizeof(Tuple));

    if (tuple_list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    tuple_list[0].key = 1; tuple_list[0].value = 10;
    tuple_list[1].key = 2; tuple_list[1].value = -5;
    tuple_list[2].key = 3; tuple_list[2].value = 20;
    tuple_list[3].key = 4; tuple_list[3].value = -10;
    tuple_list[4].key = 5; tuple_list[4].value = 15;

    int max_agg = calculate_max_aggregate(tuple_list, num_tuples);

    printf("Maximum aggregate: %d\n", max_agg);

    free(tuple_list);
    tuple_list = NULL;

    return EXIT_SUCCESS;
}