#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int id;
    int *values;
    size_t count;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
    size_t capacity;
} TupleList;

TupleList* create_tuple_list(size_t capacity) {
    if (capacity == 0) capacity = 1;
    if (capacity > SIZE_MAX / sizeof(Tuple)) return NULL;
    
    TupleList *list = (TupleList*)malloc(sizeof(TupleList));
    if (!list) return NULL;
    
    list->tuples = (Tuple*)malloc(capacity * sizeof(Tuple));
    if (!list->tuples) {
        free(list);
        return NULL;
    }
    
    list->count = 0;
    list->capacity = capacity;
    return list;
}

void free_tuple_list(TupleList *list) {
    if (!list) return;
    for (size_t i = 0; i < list->count; i++) {
        free(list->tuples[i].values);
    }
    free(list->tuples);
    free(list);
}

int add_tuple(TupleList *list, int id, const int *values, size_t count) {
    if (!list || (!values && count > 0)) return -1;
    if (count > SIZE_MAX / sizeof(int)) return -1;
    
    if (list->count >= list->capacity) {
        size_t new_capacity = list->capacity > 0 ? list->capacity * 2 : 1;
        if (new_capacity < list->capacity || new_capacity > SIZE_MAX / sizeof(Tuple)) return -1;
        
        Tuple *new_tuples = (Tuple*)realloc(list->tuples, new_capacity * sizeof(Tuple));
        if (!new_tuples) return -1;
        
        list->tuples = new_tuples;
        list->capacity = new_capacity;
    }
    
    Tuple *t = &list->tuples[list->count];
    t->id = id;
    t->count = count;
    
    if (count > 0) {
        t->values = (int*)malloc(count * sizeof(int));
        if (!t->values) return -1;
        for (size_t k = 0; k < count; k++) {
            t->values[k] = values[k];
        }
    } else {
        t->values = NULL;
    }
    
    list->count++;
    return 0;
}

TupleList* join_tuples(const TupleList *input) {
    if (!input) return NULL;
    
    TupleList *result = create_tuple_list(input->capacity);
    if (!result) return NULL;
    
    for (size_t i = 0; i < input->count; i++) {
        int found = 0;
        for (size_t j = 0; j < result->count; j++) {
            if (result->tuples[j].id == input->tuples[i].id) {
                if (SIZE_MAX - result->tuples[j].count < input->tuples[i].count) {
                    free_tuple_list(result);
                    return NULL;
                }
                
                size_t new_count = result->tuples[j].count + input->tuples[i].count;
                if (new_count > SIZE_MAX / sizeof(int)) {
                    free_tuple_list(result);
                    return NULL;
                }
                
                int *new_values = (int*)realloc(result->tuples[j].values, new_count * sizeof(int));
                if (!new_values) {
                    free_tuple_list(result);
                    return NULL;
                }
                
                if (input->tuples[i].count > 0) {
                    for (size_t k = 0; k < input->tuples[i].count; k++) {
                        new_values[result->tuples[j].count + k] = input->tuples[i].values[k];
                    }
                }
                
                result->tuples[j].values = new_values;
                result->tuples[j].count = new_count;
                found = 1;
                break;
            }
        }
        
        if (!found) {
            if (add_tuple(result, input->tuples[i].id, input->tuples[i].values, input->tuples[i].count) != 0) {
                free_tuple_list(result);
                return NULL;
            }
        }
    }
    
    return result;
}

int main(void) {
    TupleList *input = create_tuple_list(4);
    if (!input) return 1;
    
    const int v1[] = {1, 2};
    const int v2[] = {3, 4};
    const int v3[] = {5};
    const int v4[] = {6, 7, 8};
    
    if (add_tuple(input, 1, v1, 2) != 0 ||
        add_tuple(input, 2, v2, 2) != 0 ||
        add_tuple(input, 1, v3, 1) != 0 ||
        add_tuple(input, 2, v4, 3) != 0) {
        free_tuple_list(input);
        return 1;
    }
    
    TupleList *joined = join_tuples(input);
    if (!joined) {
        free_tuple_list(input);
        return 1;
    }
    
    for (size_t i = 0; i < joined->count; i++) {
        printf("ID: %d, Values: ", joined->tuples[i].id);
        for (size_t j = 0; j < joined->tuples[i].count; j++) {
            printf("%d ", joined->tuples[i].values[j]);
        }
        printf("\n");
    }
    
    free_tuple_list(input);
    free_tuple_list(joined);
    
    return 0;
}