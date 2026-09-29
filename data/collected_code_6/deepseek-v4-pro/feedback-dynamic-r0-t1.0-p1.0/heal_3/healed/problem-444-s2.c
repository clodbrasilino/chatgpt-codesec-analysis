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
        if (list->tuples[i].elements == NULL || k >= list->tuples[i].size) {
            result->tuples[i].elements = NULL;
            result->tuples[i].size = 0;
            continue;
        }

        int new_size = list->tuples[i].size - k;
        result->tuples[i].elements = (int*)malloc(sizeof(int) * new_size);
        if (result->tuples[i].elements == NULL) {
            for (int j = 0; j < i; j++) {
                free(result->tuples[j].elements);
            }
            free(result->tuples);
            free(result);
            return NULL;
        }

        result->tuples[i].size = new_size;
        for (int j = 0; j < new_size; j++) {
            result->tuples[i].elements[j] = list->tuples[i].elements[j + k];
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

    list->count = 4;
    list->tuples = (Tuple*)calloc(list->count, sizeof(Tuple));
    if (list->tuples == NULL) {
        free(list);
        return 1;
    }

    int tuple1[] = {3, 2, 1};
    int tuple2[] = {4, 9, 2};
    int tuple3[] = {1, 2, 3};
    int tuple4[] = {8, 2, 1};

    list->tuples[0].elements = tuple1;
    list->tuples[0].size = 3;
    list->tuples[1].elements = tuple2;
    list->tuples[1].size = 3;
    list->tuples[2].elements = tuple3;
    list->tuples[2].size = 3;
    list->tuples[3].elements = tuple4;
    list->tuples[3].size = 3;

    printf("[");
    TupleList *trimmed = trim_tuples(list, 2);
    if (trimmed != NULL) {
        for (int i = 0; i < trimmed->count; i++) {
            printf("(");
            for (int j = 0; j < trimmed->tuples[i].size; j++) {
                if (j > 0) {
                    printf(", ");
                }
                printf("%d", trimmed->tuples[i].elements[j]);
            }
            printf(")");
            if (i < trimmed->count - 1) {
                printf(", ");
            }
        }
        free_tuple_list(trimmed);
    }
    printf("]\n");

    free(list->tuples);
    free(list);

    return 0;
}