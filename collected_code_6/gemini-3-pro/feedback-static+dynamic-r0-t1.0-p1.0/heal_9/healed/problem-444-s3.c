#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int *elements;
    size_t size;
    size_t capacity;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
    size_t capacity;
} TupleList;

TupleList* trimTuples(const TupleList *list, size_t k) {
    if (!list) return NULL;
    
    TupleList *trimmedList = (TupleList *)malloc(sizeof(TupleList));
    if (!trimmedList) return NULL;
    
    trimmedList->count = list->count;
    trimmedList->capacity = list->capacity;
    
    if (trimmedList->capacity > 0) {
        trimmedList->tuples = (Tuple *)malloc(trimmedList->capacity * sizeof(Tuple));
        if (!trimmedList->tuples) {
            free(trimmedList);
            return NULL;
        }
    } else {
        trimmedList->tuples = NULL;
    }

    for (size_t i = 0; i < list->count; i++) {
        size_t newSize = (list->tuples[i].size > k) ? k : list->tuples[i].size;
        
        trimmedList->tuples[i].size = newSize;
        trimmedList->tuples[i].capacity = newSize;
        
        if (newSize > 0) {
            trimmedList->tuples[i].elements = (int *)malloc(newSize * sizeof(int));
            if (trimmedList->tuples[i].elements && list->tuples[i].elements) {
                memcpy(trimmedList->tuples[i].elements, list->tuples[i].elements, newSize * sizeof(int));
            }
        } else {
            trimmedList->tuples[i].elements = NULL;
        }
    }
    
    return trimmedList;
}

void freeTupleList(TupleList *list) {
    if (!list) return;
    if (list->tuples) {
        for (size_t i = 0; i < list->count; i++) {
            if (list->tuples[i].elements) {
                free(list->tuples[i].elements);
            }
        }
        free(list->tuples);
    }
    free(list);
}

int main(void) {
    TupleList list;
    list.count = 2;
    list.capacity = 2;
    list.tuples = (Tuple *)malloc(list.capacity * sizeof(Tuple));

    list.tuples[0].size = 5;
    list.tuples[0].capacity = 5;
    list.tuples[0].elements = (int *)malloc(5 * sizeof(int));
    for (int i = 0; i < 5; i++) {
        list.tuples[0].elements[i] = i + 1;
    }

    list.tuples[1].size = 3;
    list.tuples[1].capacity = 3;
    list.tuples[1].elements = (int *)malloc(3 * sizeof(int));
    for (int i = 0; i < 3; i++) {
        list.tuples[1].elements[i] = (i + 1) * 10;
    }

    TupleList *trimmed = trimTuples(&list, 2);

    if (trimmed) {
        for (size_t i = 0; i < trimmed->count; i++) {
            for (size_t j = 0; j < trimmed->tuples[i].size; j++) {
                printf("%d ", trimmed->tuples[i].elements[j]);
            }
            printf("\n");
        }
        freeTupleList(trimmed);
    }

    free(list.tuples[0].elements);
    free(list.tuples[1].elements);
    free(list.tuples);

    return 0;
}