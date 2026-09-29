#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if (!list || !values) return -1;
    if (list->count >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        Tuple *new_tuples = (Tuple*)realloc(list->tuples, new_capacity * sizeof(Tuple));
        if (!new_tuples) return -1;
        list->tuples = new_tuples;
        list->capacity = new_capacity;
    }
    
    Tuple *t = &list->tuples[list->count];
    t->id = id;
    t->count = count;
    t->values = (int*)malloc(count * sizeof(int));
    if (!t->values) return -1;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(t->values, values, count * sizeof(int));
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
                size_t new_count = result->tuples[j].count + input->tuples[i].count;
                int *new_values = (int*)realloc(result->tuples[j].values, new_count * sizeof(int));
                if (!new_values) {
                    free_tuple_list(result);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(new_values + result->tuples[j].count, input->tuples[i].values, input->tuples[i].count * sizeof(int));
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
    
    /* Possible weaknesses found:
     *  Variable 'v1' can be declared as const array [constVariable]
     */
    int v1[] = {1, 2};
    /* Possible weaknesses found:
     *  Variable 'v2' can be declared as const array [constVariable]
     */
    int v2[] = {3, 4};
    /* Possible weaknesses found:
     *  Variable 'v3' can be declared as const array [constVariable]
     */
    int v3[] = {5};
    /* Possible weaknesses found:
     *  Variable 'v4' can be declared as const array [constVariable]
     */
    int v4[] = {6, 7, 8};
    
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