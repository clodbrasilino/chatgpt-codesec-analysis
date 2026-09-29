#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

int sum_tuple_elements(const TupleList *tuple_list, long long *total_sum) {
    if (tuple_list == NULL || total_sum == NULL) {
        return -1;
    }

    *total_sum = 0;

    for (size_t i = 0; i < tuple_list->count; i++) {
        if (tuple_list->tuples[i].elements == NULL) {
            return -1; 
        }
        for (size_t j = 0; j < tuple_list->tuples[i].size; j++) {
            *total_sum += tuple_list->tuples[i].elements[j];
        }
    }

    return 0; 
}

void free_tuple_list(TupleList *tuple_list) {
    if (tuple_list != NULL) {
        if (tuple_list->tuples != NULL) {
            for (size_t i = 0; i < tuple_list->count; i++) {
                free(tuple_list->tuples[i].elements);
            }
            free(tuple_list->tuples);
        }
        tuple_list->tuples = NULL;
        tuple_list->count = 0;
    }
}

int main(void) {
    TupleList list;
    list.count = 2;
    list.tuples = (Tuple *)malloc(list.count * sizeof(Tuple));
    
    if (list.tuples == NULL) {
        return EXIT_FAILURE;
    }

    list.tuples[0].size = 3;
    list.tuples[0].elements = (int *)malloc(list.tuples[0].size * sizeof(int));
    if (list.tuples[0].elements == NULL) {
        free(list.tuples);
        return EXIT_FAILURE;
    }
    list.tuples[0].elements[0] = 1;
    list.tuples[0].elements[1] = 2;
    list.tuples[0].elements[2] = 3;

    list.tuples[1].size = 2;
    list.tuples[1].elements = (int *)malloc(list.tuples[1].size * sizeof(int));
    if (list.tuples[1].elements == NULL) {
        free(list.tuples[0].elements);
        free(list.tuples);
        return EXIT_FAILURE;
    }
    list.tuples[1].elements[0] = 4;
    list.tuples[1].elements[1] = 5;

    long long total_sum = 0;
    int result = sum_tuple_elements(&list, &total_sum);

    if (result == 0) {
        printf("Sum: %lld\n", total_sum);
    } else {
        printf("Error calculating sum.\n");
    }

    free_tuple_list(&list);

    return EXIT_SUCCESS;
}