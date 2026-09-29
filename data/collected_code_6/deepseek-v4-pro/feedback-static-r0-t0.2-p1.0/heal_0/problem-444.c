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
    result->tuples = (Tuple*)malloc(sizeof(Tuple) * list->count);
    if (result->tuples == NULL) {
        free(result);
        return NULL;
    }

    for (int i = 0; i < list->count; i++) {
        if (list->tuples[i].elements == NULL || list->tuples[i].size < 0) {
            for (int j = 0; j < i; j++) {
                free(result->tuples[j].elements);
            }
            free(result->tuples);
            free(result);
            return NULL;
        }

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

    int tuple1[] = {1, 2, 3, 4, 5};
    int tuple2[] = {10, 20, 30};
    int tuple3[] = {7, 8};

    list->tuples[0].elements = tuple1;
    list->tuples[0].size = 5;
    list->tuples[1].elements = tuple2;
    list->tuples[1].size = 3;
    list->tuples[2].elements = tuple3;
    list->tuples[2].size = 2;

    TupleList *trimmed = trim_tuples(list, 2);
    if (trimmed == NULL) {
        free(list->tuples);
        free(list);
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
    free(list->tuples);
    free(list);

    return 0;
}