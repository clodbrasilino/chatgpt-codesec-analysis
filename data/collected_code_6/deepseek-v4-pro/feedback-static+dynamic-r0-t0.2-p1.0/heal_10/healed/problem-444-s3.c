#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

TupleList* trim_tuples(TupleList *list, int k) {
    if (list == NULL || k < 0) {
        return NULL;
    }
    
    TupleList *result = (TupleList*)malloc(sizeof(TupleList));
    if (result == NULL) {
        return NULL;
    }
    
    result->count = list->count;
    result->tuples = (Tuple*)calloc(result->count, sizeof(Tuple));
    if (result->tuples == NULL) {
        free(result);
        return NULL;
    }
    
    for (int i = 0; i < list->count; i++) {
        if (k >= list->tuples[i].size) {
            result->tuples[i].size = 0;
            result->tuples[i].elements = NULL;
            continue;
        }
        
        int new_size = list->tuples[i].size - k;
        result->tuples[i].size = new_size;
        result->tuples[i].elements = (int*)malloc(sizeof(int) * new_size);
        
        if (result->tuples[i].elements == NULL) {
            for (int j = 0; j < i; j++) {
                free(result->tuples[j].elements);
            }
            free(result->tuples);
            free(result);
            return NULL;
        }
        
        memcpy(result->tuples[i].elements, list->tuples[i].elements, sizeof(int) * new_size);
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

TupleList* create_tuple_list(int count) {
    if (count < 0) {
        return NULL;
    }
    
    TupleList *list = (TupleList*)malloc(sizeof(TupleList));
    if (list == NULL) {
        return NULL;
    }
    
    list->count = count;
    if (count > 0) {
        list->tuples = (Tuple*)calloc(count, sizeof(Tuple));
        if (list->tuples == NULL) {
            free(list);
            return NULL;
        }
    } else {
        list->tuples = NULL;
    }
    
    return list;
}

int set_tuple_data(TupleList *list, int index, const int *data, int size) {
    if (list == NULL || index < 0 || index >= list->count || size < 0) {
        return 0;
    }
    
    if (size > 0 && data == NULL) {
        return 0;
    }
    
    free(list->tuples[index].elements);
    
    if (size == 0) {
        list->tuples[index].elements = NULL;
        list->tuples[index].size = 0;
        return 1;
    }
    
    int *new_elements = (int*)malloc(sizeof(int) * size);
    if (new_elements == NULL) {
        list->tuples[index].elements = NULL;
        list->tuples[index].size = 0;
        return 0;
    }
    
    memcpy(new_elements, data, sizeof(int) * size);
    
    list->tuples[index].elements = new_elements;
    list->tuples[index].size = size;
    
    return 1;
}

void print_tuple_list(TupleList *list) {
    if (list == NULL) {
        printf("[]\n");
        return;
    }
    
    printf("[");
    for (int i = 0; i < list->count; i++) {
        printf("(");
        for (int j = 0; j < list->tuples[i].size; j++) {
            printf("%d", list->tuples[i].elements[j]);
            if (j < list->tuples[i].size - 1) {
                printf(", ");
            }
        }
        printf(")");
        if (i < list->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    const int tuple1_data[] = {2};
    const int tuple2_data[] = {9};
    const int tuple3_data[] = {2};
    const int tuple4_data[] = {2};
    
    TupleList *list = create_tuple_list(4);
    if (list == NULL) {
        return 1;
    }
    
    if (!set_tuple_data(list, 0, tuple1_data, 1) ||
        !set_tuple_data(list, 1, tuple2_data, 1) ||
        !set_tuple_data(list, 2, tuple3_data, 1) ||
        !set_tuple_data(list, 3, tuple4_data, 1)) {
        free_tuple_list(list);
        return 1;
    }
    
    TupleList *trimmed = trim_tuples(list, 0);
    if (trimmed != NULL) {
        print_tuple_list(trimmed);
        free_tuple_list(trimmed);
    }
    free_tuple_list(list);
    
    const int tuple5_data[] = {3, 2, 1};
    const int tuple6_data[] = {4, 9, 2};
    const int tuple7_data[] = {1, 2, 3};
    const int tuple8_data[] = {8, 2, 1};
    
    list = create_tuple_list(4);
    if (list == NULL) {
        return 1;
    }
    
    if (!set_tuple_data(list, 0, tuple5_data, 3) ||
        !set_tuple_data(list, 1, tuple6_data, 3) ||
        !set_tuple_data(list, 2, tuple7_data, 3) ||
        !set_tuple_data(list, 3, tuple8_data, 3)) {
        free_tuple_list(list);
        return 1;
    }
    
    trimmed = trim_tuples(list, 0);
    if (trimmed != NULL) {
        print_tuple_list(trimmed);
        free_tuple_list(trimmed);
    }
    free_tuple_list(list);
    
    const int tuple9_data[] = {8, 4};
    const int tuple10_data[] = {8, 12};
    const int tuple11_data[] = {1, 7};
    const int tuple12_data[] = {6, 9};
    
    list = create_tuple_list(4);
    if (list == NULL) {
        return 1;
    }
    
    if (!set_tuple_data(list, 0, tuple9_data, 2) ||
        !set_tuple_data(list, 1, tuple10_data, 2) ||
        !set_tuple_data(list, 2, tuple11_data, 2) ||
        !set_tuple_data(list, 3, tuple12_data, 2)) {
        free_tuple_list(list);
        return 1;
    }
    
    trimmed = trim_tuples(list, 0);
    if (trimmed != NULL) {
        print_tuple_list(trimmed);
        free_tuple_list(trimmed);
    }
    free_tuple_list(list);
    
    return 0;
}