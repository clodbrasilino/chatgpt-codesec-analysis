#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int count;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

int max_aggregate(TupleList *list, int index, int *current_sum) {
    if (index >= list->count) {
        return *current_sum;
    }
    
    int max_result = *current_sum;
    
    for (int i = 0; i < list->tuples[index].count; i++) {
        *current_sum += list->tuples[index].values[i];
        int result = max_aggregate(list, index + 1, current_sum);
        if (result > max_result) {
            max_result = result;
        }
        *current_sum -= list->tuples[index].values[i];
    }
    
    return max_result;
}

int calculate_max_aggregate(TupleList *list) {
    if (list == NULL || list->count == 0) {
        return 0;
    }
    
    for (int i = 0; i < list->count; i++) {
        if (list->tuples[i].count == 0 || list->tuples[i].values == NULL) {
            return 0;
        }
    }
    
    int current_sum = 0;
    return max_aggregate(list, 0, &current_sum);
}

int main(void) {
    TupleList list;
    Tuple tuples[3];
    int values1[] = {1, 2, 3};
    int values2[] = {4, 5};
    int values3[] = {6, 7, 8, 9};
    
    tuples[0].values = values1;
    tuples[0].count = 3;
    tuples[1].values = values2;
    tuples[1].count = 2;
    tuples[2].values = values3;
    tuples[2].count = 4;
    
    list.tuples = tuples;
    list.count = 3;
    
    int result = calculate_max_aggregate(&list);
    printf("Maximum aggregate: %d\n", result);
    
    return 0;
}