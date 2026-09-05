#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int *data;
    size_t num_cols;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t num_tuples;
} TupleList;

int find_max_nth_column(const TupleList *list, size_t n, int *result) {
    if (list == NULL || result == NULL || list->tuples == NULL || list->num_tuples == 0) {
        return -1;
    }
    
    if (n == 0 || n > list->tuples[0].num_cols) {
        return -1;
    }
    
    int max = INT_MIN;
    size_t col_index = n - 1;
    
    for (size_t i = 0; i < list->num_tuples; i++) {
        if (list->tuples[i].data == NULL || list->tuples[i].num_cols <= col_index) {
            return -1;
        }
        
        if (list->tuples[i].data[col_index] > max) {
            max = list->tuples[i].data[col_index];
        }
    }
    
    *result = max;
    return 0;
}

void free_tuple_list(TupleList *list) {
    if (list == NULL) {
        return;
    }
    
    if (list->tuples != NULL) {
        for (size_t i = 0; i < list->num_tuples; i++) {
            free(list->tuples[i].data);
            list->tuples[i].data = NULL;
        }
        free(list->tuples);
        list->tuples = NULL;
    }
    list->num_tuples = 0;
}

int main(void) {
    TupleList list = {0};
    size_t num_tuples = 3;
    size_t num_cols = 4;
    
    list.tuples = malloc(num_tuples * sizeof(Tuple));
    if (list.tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    list.num_tuples = num_tuples;
    
    int values[][4] = {
        {10, 20, 30, 40},
        {15, 25, 35, 45},
        {5, 50, 25, 35}
    };
    
    for (size_t i = 0; i < num_tuples; i++) {
        list.tuples[i].data = malloc(num_cols * sizeof(int));
        if (list.tuples[i].data == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_tuple_list(&list);
            return EXIT_FAILURE;
        }
        list.tuples[i].num_cols = num_cols;
        
        for (size_t j = 0; j < num_cols; j++) {
            list.tuples[i].data[j] = values[i][j];
        }
    }
    
    size_t n = 2;
    int max_value;
    
    if (find_max_nth_column(&list, n, &max_value) == 0) {
        printf("Maximum of column %zu: %d\n", n, max_value);
    } else {
        fprintf(stderr, "Error finding maximum\n");
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }
    
    free_tuple_list(&list);
    return EXIT_SUCCESS;
}