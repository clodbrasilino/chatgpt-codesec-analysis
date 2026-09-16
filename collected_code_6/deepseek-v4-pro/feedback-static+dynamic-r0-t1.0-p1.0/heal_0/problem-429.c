#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple* tuples;
    int size;
    int capacity;
} TupleList;

void initializeTupleList(TupleList* list) {
    list->size = 0;
    list->capacity = 10;
    list->tuples = (Tuple*)malloc(list->capacity * sizeof(Tuple));
    if (list->tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

void addTuple(TupleList* list, int first, int second) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        Tuple* newTuples = (Tuple*)realloc(list->tuples, list->capacity * sizeof(Tuple));
        if (newTuples == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            free(list->tuples);
            exit(EXIT_FAILURE);
        }
        list->tuples = newTuples;
    }
    list->tuples[list->size].first = first;
    list->tuples[list->size].second = second;
    list->size++;
}

void freeTupleList(TupleList* list) {
    free(list->tuples);
    list->tuples = NULL;
    list->size = 0;
    list->capacity = 0;
}

void extractElementwise(const Tuple* tuple1, int size1, const Tuple* tuple2, int size2, TupleList* result) {
    int minSize = (size1 < size2) ? size1 : size2;
    
    for (int i = 0; i < minSize; i++) {
        addTuple(result, tuple1[i].first + tuple2[i].first, 
                        tuple1[i].second + tuple2[i].second);
    }
}

void extractTuples(const Tuple* tuple1, int size1, const Tuple* tuple2, int size2, TupleList* result) {
    for (int i = 0; i < size1; i++) {
        addTuple(result, tuple1[i].first, tuple1[i].second);
    }
    for (int i = 0; i < size2; i++) {
        addTuple(result, tuple2[i].first, tuple2[i].second);
    }
}

void printTupleList(const TupleList* list) {
    printf("[");
    for (int i = 0; i < list->size; i++) {
        printf("(%d, %d)", list->tuples[i].first, list->tuples[i].second);
        if (i < list->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() {
    Tuple tuple1[] = {{1, 2}, {3, 4}, {5, 6}};
    Tuple tuple2[] = {{7, 8}, {9, 10}};
    
    int size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    int size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    
    TupleList elementwiseResult;
    TupleList tuplesResult;
    
    initializeTupleList(&elementwiseResult);
    initializeTupleList(&tuplesResult);
    
    extractElementwise(tuple1, size1, tuple2, size2, &elementwiseResult);
    extractTuples(tuple1, size1, tuple2, size2, &tuplesResult);
    
    printf("Elementwise: ");
    printTupleList(&elementwiseResult);
    
    printf("Tuples: ");
    printTupleList(&tuplesResult);
    
    freeTupleList(&elementwiseResult);
    freeTupleList(&tuplesResult);
    
    return 0;
}