#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

TupleList* trimTuples(const TupleList *inputList, size_t k) {
    if (!inputList) return NULL;

    TupleList *resultList = malloc(sizeof(TupleList));
    if (!resultList) return NULL;

    size_t alloc_count = inputList->count > 0 ? inputList->count : 1;
    resultList->tuples = malloc(