#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;
 /* Possible weaknesses found:
  *  test case 0 failed: expected '[(2,), (9,), (2,), (2,)]', got <no output>
  *  test case 1 failed: expected '[(3, 2, 1), (4, 9, 2), (1, 2, 3), (8, 2, 1)]', got <no output>
  *  test case 2 failed: expected '[(8, 4), (8, 12), (1, 7), (6, 9)]', got <no output>
  */

TupleList* trim_tuples(TupleList *list, int k) {
    if (list == NULL || k < 0) {
        return NULL;
    }
    
    TupleList *result = (TupleList*)malloc(sizeof(TupleList));
    if (result == NULL) {
        return NULL;
    }
    
    result->count = list->count;
    result->tuples = (Tuple*)malloc(sizeof(Tuple) * result->count);
    if (result->tuples == NULL) {
        free(result);
        return NULL;
    }
    
    for (int i = 0; i < list->count; i++) {
        int new_size = list->tuples[i].size - k;
        if (new_size < 0) {
            new_size = 0;
        }
        
        result->tuples[i].size = new_size;
        result->tuples[i].elements = (int*)malloc(sizeof(int) * new_size);
        if (result->tuples[i].elements == NULL && new_size > 0) {
            for (int j = 0; j < i; j++) {
                free(result->tuples[j].elements);
            }
            free(result->tuples);
            free(result);
            return NULL;
        }
        
        for (int j = 0; j < new_size; j++) {
            result->tuples[i].elements[j] = list->tuples[i].elements[j];
        }
    }
    
    return result;
}

void free_tuple_list(TupleList *list) {
    if (list == NULL) {
        return;
    }
    
    for (int i = 0; i < list->count; i++) {
        free(list->tuples[i].elements);
    }
    free(list->tuples);
    free(list);
}

int main(void) {
    TupleList *list = (TupleList*)malloc(sizeof(TupleList));
    if (list == NULL) {
        return 1;
    }
    
    list->count = 3;
    list->tuples = (Tuple*)malloc(sizeof(Tuple) * list->count);
    if (list->tuples == NULL) {
        free(list);
        return 1;
    }
    
    const int tuple1_data[] = {1, 2, 3, 4, 5};
    const int tuple2_data[] = {10, 20, 30};
    const int tuple3_data[] = {7, 8, 9, 10, 11, 12};
    
    list->tuples[0].size = 5;
    list->tuples[0].elements = (int*)malloc(sizeof(int) * 5);
    if (list->tuples[0].elements == NULL) {
        free(list->tuples);
        free(list);
        return 1;
    }
    for (int i = 0; i < 5; i++) {
        list->tuples[0].elements[i] = tuple1_data[i];
    }
    
    list->tuples[1].size = 3;
    list->tuples[1].elements = (int*)malloc(sizeof(int) * 3);
    if (list->tuples[1].elements == NULL) {
        free(list->tuples[0].elements);
        free(list->tuples);
        free(list);
        return 1;
    }
    for (int i = 0; i < 3; i++) {
        list->tuples[1].elements[i] = tuple2_data[i];
    }
    
    list->tuples[2].size = 6;
    list->tuples[2].elements = (int*)malloc(sizeof(int) * 6);
    if (list->tuples[2].elements == NULL) {
        free(list->tuples[0].elements);
        free(list->tuples[1].elements);
        free(list->tuples);
        free(list);
        return 1;
    }
    for (int i = 0; i < 6; i++) {
        list->tuples[2].elements[i] = tuple3_data[i];
    }
    
    TupleList *trimmed = trim_tuples(list, 2);
    if (trimmed == NULL) {
        free_tuple_list(list);
        return 1;
    }
    
    for (int i = 0; i < trimmed->count; i++) {
        printf("Tuple %d: ", i);
        for (int j = 0; j < trimmed->tuples[i].size; j++) {
            printf("%d ", trimmed->tuples[i].elements[j]);
        }
        printf("\n");
    }
    
    free_tuple_list(trimmed);
    free_tuple_list(list);
    
    return 0;
}