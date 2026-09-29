#include <stdio.h>
#include <stdlib.h>

typedef struct TupleNode {
    int *data;
    int size;
    struct TupleNode **subtuples;
    int subtuple_count;
} TupleNode;

TupleNode *create_tuple(const int *data, int size, TupleNode **subtuples, int subtuple_count);
void free_tuple(TupleNode *tuple);
TupleNode *add_tuples(TupleNode *tuple1, TupleNode *tuple2, int *error);
void print_tuple(TupleNode *tuple);

TupleNode *create_tuple(const int *data, int size, TupleNode **subtuples, int subtuple_count) {
    TupleNode *tuple = (TupleNode *)malloc(sizeof(TupleNode));
    if (tuple == NULL) {
        return NULL;
    }
    
    tuple->size = size;
    tuple->subtuple_count = subtuple_count;
    
    if (size > 0) {
        tuple->data = (int *)malloc(size * sizeof(int));
        if (tuple->data == NULL) {
            free(tuple);
            return NULL;
        }
        for (int i = 0; i < size; i++) {
            tuple->data[i] = data[i];
        }
    } else {
        tuple->data = NULL;
    }
    
    if (subtuple_count > 0) {
        tuple->subtuples = (TupleNode **)malloc(subtuple_count * sizeof(TupleNode *));
        if (tuple->subtuples == NULL) {
            free(tuple->data);
            free(tuple);
            return NULL;
        }
        for (int i = 0; i < subtuple_count; i++) {
            tuple->subtuples[i] = subtuples[i];
        }
    } else {
        tuple->subtuples = NULL;
    }
    
    return tuple;
}

void free_tuple(TupleNode *tuple) {
    if (tuple == NULL) {
        return;
    }
    
    if (tuple->data != NULL) {
        free(tuple->data);
    }
    
    if (tuple->subtuples != NULL) {
        for (int i = 0; i < tuple->subtuple_count; i++) {
            free_tuple(tuple->subtuples[i]);
        }
        free(tuple->subtuples);
    }
    
    free(tuple);
}

TupleNode *add_tuples(TupleNode *tuple1, TupleNode *tuple2, int *error) {
    *error = 0;
    
    if (tuple1 == NULL || tuple2 == NULL) {
        *error = 1;
        return NULL;
    }
    
    if (tuple1->size != tuple2->size) {
        *error = 2;
        return NULL;
    }
    
    int result_size = tuple1->size;
    int *result_data = NULL;
    
    if (result_size > 0) {
        result_data = (int *)malloc(result_size * sizeof(int));
        if (result_data == NULL) {
            *error = 3;
            return NULL;
        }
        
        for (int i = 0; i < result_size; i++) {
            result_data[i] = tuple1->data[i] + tuple2->data[i];
        }
    }
    
    int result_subtuple_count = tuple1->subtuple_count;
    TupleNode **result_subtuples = NULL;
    
    if (result_subtuple_count > 0) {
        result_subtuples = (TupleNode **)malloc(result_subtuple_count * sizeof(TupleNode *));
        if (result_subtuples == NULL) {
            free(result_data);
            *error = 3;
            return NULL;
        }
        
        for (int i = 0; i < result_subtuple_count; i++) {
            result_subtuples[i] = add_tuples(tuple1->subtuples[i], tuple2->subtuples[i], error);
            if (*error != 0) {
                for (int j = 0; j < i; j++) {
                    free_tuple(result_subtuples[j]);
                }
                free(result_subtuples);
                free(result_data);
                return NULL;
            }
        }
    }
    
    TupleNode *result = create_tuple(result_data, result_size, result_subtuples, result_subtuple_count);
    free(result_data);
    
    if (result == NULL) {
        *error = 4;
        if (result_subtuples != NULL) {
            for (int i = 0; i < result_subtuple_count; i++) {
                free_tuple(result_subtuples[i]);
            }
            free(result_subtuples);
        }
        return NULL;
    }
    
    if (result_subtuples != NULL) {
        free(result_subtuples);
    }
    
    return result;
}

void print_tuple(TupleNode *tuple) {
    if (tuple == NULL) {
        printf("NULL");
        return;
    }
    
    printf("(");
    
    for (int i = 0; i < tuple->size; i++) {
        printf("%d", tuple->data[i]);
        if (i < tuple->size - 1 || tuple->subtuple_count > 0) {
            printf(", ");
        }
    }
    
    for (int i = 0; i < tuple->subtuple_count; i++) {
        print_tuple(tuple->subtuples[i]);
        if (i < tuple->subtuple_count - 1) {
            printf(", ");
        }
    }
    
    printf(")");
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'data1' can be declared as const array [constVariable]
     */
    int data1[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'data2' is assigned a value that is never used. [unreadVariable]
     */
    int data2[] = {4, 5, 6};
    /* Possible weaknesses found:
     *  Variable 'data3' can be declared as const array [constVariable]
     */
    int data3[] = {7, 8};
    /* Possible weaknesses found:
     *  Variable 'data4' can be declared as const array [constVariable]
     */
    int data4[] = {9, 10};
    
    TupleNode *subtuple1 = create_tuple(data3, 2, NULL, 0);
    TupleNode *subtuple2 = create_tuple(data4, 2, NULL, 0);
    
    TupleNode *subtuples1[] = {subtuple1, subtuple2};
    
    TupleNode *tuple1 = create_tuple(data1, 3, subtuples1, 2);
    
    /* Possible weaknesses found:
     *  Variable 'data5' can be declared as const array [constVariable]
     */
    int data5[] = {11, 12, 13};
    /* Possible weaknesses found:
     *  Variable 'data6' can be declared as const array [constVariable]
     */
    int data6[] = {14, 15};
    /* Possible weaknesses found:
     *  Variable 'data7' can be declared as const array [constVariable]
     */
    int data7[] = {16, 17};
    
    TupleNode *subtuple3 = create_tuple(data6, 2, NULL, 0);
    TupleNode *subtuple4 = create_tuple(data7, 2, NULL, 0);
    
    TupleNode *subtuples2[] = {subtuple3, subtuple4};
    
    TupleNode *tuple2 = create_tuple(data5, 3, subtuples2, 2);
    
    int error;
    TupleNode *result = add_tuples(tuple1, tuple2, &error);
    
    if (error == 0) {
        printf("Result: ");
        print_tuple(result);
        printf("\n");
    } else {
        printf("Error: %d\n", error);
    }
    
    free_tuple(result);
    free_tuple(tuple1);
    free_tuple(tuple2);
    
    return 0;
}