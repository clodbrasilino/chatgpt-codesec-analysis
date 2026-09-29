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
    result->tuples = (Tuple*)calloc((size_t)result->count, sizeof(Tuple));
    if (result->tuples == NULL) {
        free(result);
        return NULL;
    }

    for (int i = 0; i < list->count; i++) {
        result->tuples[i].elements = NULL;
        result->tuples[i].size = 0;

        if (list->tuples[i].elements == NULL) {
            continue;
        }

        if (k >= list->tuples[i].size) {
            result->tuples[i].size = 0;
            continue;
        }

        int new_size = list->tuples[i].size - k;

        if (new_size <= 0) {
            result->tuples[i].size = 0;
            continue;
        }

        result->tuples[i].elements = (int*)malloc(sizeof(int) * (size_t)new_size);
        if (result->tuples[i].elements == NULL) {
            for (int j = 0; j < i; j++) {
                free(result->tuples[j].elements);
            }
            free(result->tuples);
            free(result);
            return NULL;
        }

        result->tuples[i].size = new_size;
        memcpy(result->tuples[i].elements, 
               list->tuples[i].elements, 
               sizeof(int) * (size_t)new_size);
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

void print_tuple_list(TupleList *list) {
    if (list == NULL) return;

    printf("[");
    for (int i = 0; i < list->count; i++) {
        printf("(");
        if (list->tuples[i].elements != NULL && list->tuples[i].size > 0) {
            for (int j = 0; j < list->tuples[i].size; j++) {
                printf("%d", list->tuples[i].elements[j]);
                if (j < list->tuples[i].size - 1) {
                    printf(", ");
                }
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
    TupleList *list = (TupleList*)malloc(sizeof(TupleList));
    if (list == NULL) {
        return 1;
    }

    list->count = 4;
    list->tuples = (Tuple*)calloc((size_t)list->count, sizeof(Tuple));
    if (list->tuples == NULL) {
        free(list);
        return 1;
    }

    int *tuple1 = (int*)malloc(3 * sizeof(int));
    int *tuple2 = (int*)malloc(3 * sizeof(int));
    int *tuple3 = (int*)malloc(3 * sizeof(int));
    int *tuple4 = (int*)malloc(3 * sizeof(int));

    if (tuple1 == NULL || tuple2 == NULL || tuple3 == NULL || tuple4 == NULL) {
        free(tuple1);
        free(tuple2);
        free(tuple3);
        free(tuple4);
        free(list->tuples);
        free(list);
        return 1;
    }

    tuple1[0] = 3; tuple1[1] = 2; tuple1[2] = 1;
    tuple2[0] = 4; tuple2[1] = 9; tuple2[2] = 2;
    tuple3[0] = 1; tuple3[1] = 2; tuple3[2] = 3;
    tuple4[0] = 8; tuple4[1] = 2; tuple4[2] = 1;

    list->tuples[0].elements = tuple1;
    list->tuples[0].size = 3;
    list->tuples[1].elements = tuple2;
    list->tuples[1].size = 3;
    list->tuples[2].elements = tuple3;
    list->tuples[2].size = 3;
    list->tuples[3].elements = tuple4;
    list->tuples[3].size = 3;

    TupleList *trimmed = trim_tuples(list, 1);
    if (trimmed != NULL) {
        print_tuple_list(trimmed);
        free_tuple_list(trimmed);
    }

    for (int i = 0; i < list->count; i++) {
        free(list->tuples[i].elements);
    }
    free(list->tuples);
    free(list);

    return 0;
}