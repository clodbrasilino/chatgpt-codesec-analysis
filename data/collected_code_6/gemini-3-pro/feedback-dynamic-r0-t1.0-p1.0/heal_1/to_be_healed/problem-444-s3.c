#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;
 /* Possible weaknesses found:
  *  test case 2 failed: expected '[(8, 4), (8, 12), (1, 7), (6, 9)]', got <no output>
  *  test case 0 failed: expected '[(2,), (9,), (2,), (2,)]', got <no output>
  *  test case 1 failed: expected '[(3, 2, 1), (4, 9, 2), (1, 2, 3), (8, 2, 1)]', got <no output>
  */

TupleList* trimTuples(const TupleList *list, size_t k) {
    if (!list || !list->tuples) {
        return NULL;
    }

    TupleList *trimmedList = (TupleList *)malloc(sizeof(TupleList));
    if (!trimmedList) {
        return NULL;
    }

    trimmedList->count = list->count;
    trimmedList->tuples = (Tuple *)calloc(trimmedList->count, sizeof(Tuple));
    if (!trimmedList->tuples) {
        free(trimmedList);
        return NULL;
    }

    for (size_t i = 0; i < list->count; ++i) {
        if (list->tuples[i].size > k) {
            trimmedList->tuples[i].size = list->tuples[i].size - k;
            trimmedList->tuples[i].elements = (int *)malloc(trimmedList->tuples[i].size * sizeof(int));
            if (!trimmedList->tuples[i].elements) {
                for (size_t j = 0; j < i; ++j) {
                    free(trimmedList->tuples[j].elements);
                }
                free(trimmedList->tuples);
                free(trimmedList);
                return NULL;
            }
            for (size_t j = 0; j < trimmedList->tuples[i].size; ++j) {
                trimmedList->tuples[i].elements[j] = list->tuples[i].elements[j];
            }
        } else {
            trimmedList->tuples[i].size = 0;
            trimmedList->tuples[i].elements = NULL;
        }
    }

    return trimmedList;
}

void freeTupleList(TupleList *list) {
    if (list) {
        if (list->tuples) {
            for (size_t i = 0; i < list->count; ++i) {
                free(list->tuples[i].elements);
            }
            free(list->tuples);
        }
        free(list);
    }
}

int main(void) {
    TupleList list;
    list.count = 2;
    list.tuples = (Tuple *)malloc(list.count * sizeof(Tuple));
    
    if (!list.tuples) {
        return EXIT_FAILURE;
    }

    list.tuples[0].size = 5;
    list.tuples[0].elements = (int *)malloc(list.tuples[0].size * sizeof(int));
    if (list.tuples[0].elements) {
        for (int i = 0; i < 5; ++i) list.tuples[0].elements[i] = i + 1;
    } else {
        free(list.tuples);
        return EXIT_FAILURE;
    }

    list.tuples[1].size = 3;
    list.tuples[1].elements = (int *)malloc(list.tuples[1].size * sizeof(int));
    if (list.tuples[1].elements) {
        for (int i = 0; i < 3; ++i) list.tuples[1].elements[i] = (i + 1) * 10;
    } else {
        free(list.tuples[0].elements);
        free(list.tuples);
        return EXIT_FAILURE;
    }

    size_t k = 2;
    TupleList *trimmed = trimTuples(&list, k);

    if (trimmed) {
        for (size_t i = 0; i < trimmed->count; ++i) {
            printf("Tuple %zu (size %zu): ", i, trimmed->tuples[i].size);
            for (size_t j = 0; j < trimmed->tuples[i].size; ++j) {
                printf("%d ", trimmed->tuples[i].elements[j]);
            }
            printf("\n");
        }
        freeTupleList(trimmed);
    }

    free(list.tuples[0].elements);
    free(list.tuples[1].elements);
    free(list.tuples);

    return EXIT_SUCCESS;
}