#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    float value;
} Tuple;

typedef struct {
    Tuple *data;
    size_t size;
    size_t capacity;
} TupleList;

int compare_tuples(const void *a, const void *b) {
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    if (tuple_a->value < tuple_b->value) return -1;
    if (tuple_a->value > tuple_b->value) return 1;
    return 0;
}

int tuple_list_init(TupleList *list, size_t initial_capacity) {
    if (list == NULL || initial_capacity == 0) {
        return -1;
    }
    list->data = (Tuple *)malloc(initial_capacity * sizeof(Tuple));
    if (list->data == NULL) {
        return -1;
    }
    list->size = 0;
    list->capacity = initial_capacity;
    return 0;
}

void tuple_list_free(TupleList *list) {
    if (list == NULL) {
        return;
    }
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

int tuple_list_push_back(TupleList *list, const Tuple *tuple) {
    if (list == NULL || tuple == NULL) {
        return -1;
    }
    if (list->size >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        Tuple *new_data = (Tuple *)realloc(list->data, new_capacity * sizeof(Tuple));
        if (new_data == NULL) {
            return -1;
        }
        list->data = new_data;
        list->capacity = new_capacity;
    }
    list->data[list->size] = *tuple;
    list->size++;
    return 0;
}

int find_min_k_records(const TupleList *list, size_t k, TupleList *result) {
    if (list == NULL || result == NULL || k == 0 || list->size == 0) {
        return -1;
    }
    
    size_t actual_k = (k < list->size) ? k : list->size;
    
    if (tuple_list_init(result, actual_k) != 0) {
        return -1;
    }
    
    Tuple *sorted_copy = (Tuple *)malloc(list->size * sizeof(Tuple));
    if (sorted_copy == NULL) {
        tuple_list_free(result);
        return -1;
    }
    
    memcpy(sorted_copy, list->data, list->size * sizeof(Tuple));
    
    qsort(sorted_copy, list->size, sizeof(Tuple), compare_tuples);
    
    for (size_t i = 0; i < actual_k; i++) {
        if (tuple_list_push_back(result, &sorted_copy[i]) != 0) {
            tuple_list_free(result);
            free(sorted_copy);
            return -1;
        }
    }
    
    free(sorted_copy);
    return 0;
}

int main(void) {
    TupleList list;
    TupleList result;
    
    if (tuple_list_init(&list, 10) != 0) {
        fprintf(stderr, "Failed to initialize tuple list\n");
        return EXIT_FAILURE;
    }
    
    Tuple tuples[] = {
        {1, "Alice", 85.5f},
        {2, "Bob", 92.3f},
        {3, "Charlie", 78.9f},
        {4, "Diana", 95.1f},
        {5, "Eve", 88.7f},
        {6, "Frank", 70.2f},
        {7, "Grace", 99.9f},
        {8, "Henry", 82.4f}
    };
    
    for (size_t i = 0; i < sizeof(tuples) / sizeof(tuples[0]); i++) {
        if (tuple_list_push_back(&list, &tuples[i]) != 0) {
            fprintf(stderr, "Failed to add tuple to list\n");
            tuple_list_free(&list);
            return EXIT_FAILURE;
        }
    }
    
    size_t k = 3;
    if (find_min_k_records(&list, k, &result) != 0) {
        fprintf(stderr, "Failed to find minimum k records\n");
        tuple_list_free(&list);
        return EXIT_FAILURE;
    }
    
    printf("Top %zu minimum records:\n", k);
    for (size_t i = 0; i < result.size; i++) {
        printf("ID: %d, Name: %s, Value: %.2f\n", 
               result.data[i].id, result.data[i].name, result.data[i].value);
    }
    
    tuple_list_free(&result);
    tuple_list_free(&list);
    
    return EXIT_SUCCESS;
}