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

        if (k >= list->tuples[i].size) {
            result->tuples[i].size = 0;
            result->tuples[i].elements = NULL;
        } else {
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

            for (int j = 0; j < new_size; j++) {
                result->tuples[i].elements[j] = list->tuples[i].elements[j + k];
            }
        }
    }

    return result;
}

void free_tuple_list(TupleList *list) {
    if (list == NULL) {
        return;
    }

    if (list->tuples != NULL) {
        for (int i = 0; i < list->count; i++) {
            if (list->tuples[i].elements != NULL) {
                free(list->tuples[i].elements);
            }
        }
        free(list->tuples);
    }
    free(list);
}

int main(void) {
    TupleList *list = (TupleList*)malloc(sizeof(TupleList));
    if (list == NULL) {
        return 1;
    }

    list->count = 3;
    list->tuples = (Tuple*)malloc(sizeof(Tuple) * 3);
    if (list->tuples == NULL) {
        free(list);
        return 1;
    }

    list->tuples[0].size = 4;
    list->tuples[0].elements = (int*)malloc(sizeof(int) * 4);
    if (list->tuples[0].elements == NULL) {
        free(list->tuples);
        free(list);
        return 1;
    }
    list->tuples[0].elements[0] = 1;
    list->tuples[0].elements[1] = 2;
    list->tuples[0].elements[2] = 3;
    list->tuples[0].elements[3] = 4;

    list->tuples[1].size = 3;
    list->tuples[1].elements = (int*)malloc(sizeof(int) * 3);
    if (list->tuples[1].elements == NULL) {
        free(list->tuples[0].elements);
        free(list->tuples);
        free(list);
        return 1;
    }
    list->tuples[1].elements[0] = 5;
    list->tuples[1].elements[1] = 6;
    list->tuples[1].elements[2] = 7;

    list->tuples[2].size = 2;
    list->tuples[2].elements = (int*)malloc(sizeof(int) * 2);
    if (list->tuples[2].elements == NULL) {
        free(list->tuples[0].elements);
        free(list->tuples[1].elements);
        free(list->tuples);
        free(list);
        return 1;
    }
    list->tuples[2].elements[0] = 8;
    list->tuples[2].elements[1] = 9;

    TupleList *trimmed = trim_tuples(list, 2);
    if (trimmed == NULL) {
        free_tuple_list(list);
        return 1;
    }

    printf("[");
    for (int i = 0; i < trimmed->count; i++) {
        printf("(");
        for (int j = 0; j < trimmed->tuples[i].size; j++) {
            printf("%d", trimmed->tuples[i].elements[j]);
            if (j < trimmed->tuples[i].size - 1) {
                printf(", ");
            }
        }
        printf(")");
        if (i < trimmed->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    free_tuple_list(trimmed);
    free_tuple_list(list);

    return 0;
}