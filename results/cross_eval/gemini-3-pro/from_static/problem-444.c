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

TupleList* trimTuples(const TupleList *inputList, size_t k) {
    if (!inputList || !inputList->tuples) {
        return NULL;
    }

    TupleList *resultList = malloc(sizeof(TupleList));
    if (!resultList) {
        return NULL;
    }

    resultList->count = inputList->count;
    resultList->tuples = malloc(resultList->count * sizeof(Tuple));
    if (!resultList->tuples) {
        free(resultList);
        return NULL;
    }

    for (size_t i = 0; i < inputList->count; i++) {
        Tuple *current = &inputList->tuples[i];
        Tuple *result = &resultList->tuples[i];

        if (current->size <= k) {
            result->size = 0;
            result->elements = NULL;
        } else {
            result->size = current->size - k;
            result->elements = malloc(result->size * sizeof(int));
            if (!result->elements) {
                for (size_t j = 0; j < i; j++) {
                    free(resultList->tuples[j].elements);
                }
                free(resultList->tuples);
                free(resultList);
                return NULL;
            }
            for (size_t j = 0; j < result->size; j++) {
                result->elements[j] = current->elements[j];
            }
        }
    }

    return resultList;
}

void freeTupleList(TupleList *list) {
    if (list) {
        if (list->tuples) {
            for (size_t i = 0; i < list->count; i++) {
                free(list->tuples[i].elements);
            }
            free(list->tuples);
        }
        free(list);
    }
}

int main(void) {
    TupleList inputList;
    inputList.count = 2;
    inputList.tuples = malloc(inputList.count * sizeof(Tuple));
    if (!inputList.tuples) {
        return 1;
    }

    inputList.tuples[0].size = 5;
    inputList.tuples[0].elements = malloc(5 * sizeof(int));
    if (inputList.tuples[0].elements) {
        for (int i = 0; i < 5; i++) inputList.tuples[0].elements[i] = i + 1;
    }

    inputList.tuples[1].size = 3;
    inputList.tuples[1].elements = malloc(3 * sizeof(int));
    if (inputList.tuples[1].elements) {
        for (int i = 0; i < 3; i++) inputList.tuples[1].elements[i] = (i + 1) * 10;
    }

    size_t k = 2;
    TupleList *trimmedList = trimTuples(&inputList, k);

    if (trimmedList) {
        for (size_t i = 0; i < trimmedList->count; i++) {
            printf("Tuple %zu: ", i);
            for (size_t j = 0; j < trimmedList->tuples[i].size; j++) {
                printf("%d ", trimmedList->tuples[i].elements[j]);
            }
            printf("\n");
        }
    }

    freeTupleList(trimmedList);
    freeTupleList(&inputList);

    return 0;
}