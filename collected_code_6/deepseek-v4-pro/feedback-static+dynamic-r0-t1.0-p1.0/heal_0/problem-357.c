#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    size_t size;
} Tuple;

int find_max_element(Tuple *tuples, size_t tuple_count) {
    if (tuples == NULL || tuple_count == 0) {
        return 0;
    }
    
    int max = tuples[0].values[0];
    size_t max_tuple_index = 0;
    size_t max_value_index = 0;
    
    for (size_t i = 0; i < tuple_count; i++) {
        if (tuples[i].values == NULL || tuples[i].size == 0) {
            continue;
        }
        for (size_t j = 0; j < tuples[i].size; j++) {
            if (tuples[i].values[j] > max) {
                max = tuples[i].values[j];
                max_tuple_index = i;
                max_value_index = j;
            }
        }
    }
    
    return max;
}

int main(void) {
    int values1[] = {3, 5, 9, 2};
    int values2[] = {12, 7, 4};
    int values3[] = {8, 1, 6};
    
    Tuple tuples[] = {
        {values1, 4},
        {values2, 3},
        {values3, 3}
    };
    
    int max = find_max_element(tuples, 3);
    printf("Maximum element: %d\n", max);
    
    return 0;
}