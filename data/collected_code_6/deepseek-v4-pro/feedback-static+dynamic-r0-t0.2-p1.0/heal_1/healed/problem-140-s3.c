#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
    int capacity;
} IntList;

typedef struct {
    int value;
    int count;
} Tuple;

void initList(IntList *list) {
    list->elements = NULL;
    list->size = 0;
    list->capacity = 0;
}

int addElement(IntList *list, int value) {
    if (list->size == list->capacity) {
        int newCapacity = list->capacity == 0 ? 4 : list->capacity * 2;
        int *newElements = (int *)realloc(list->elements, newCapacity * sizeof(int));
        if (newElements == NULL) {
            return 0;
        }
        list->elements = newElements;
        list->capacity = newCapacity;
    }
    list->elements[list->size++] = value;
    return 1;
}

void freeList(IntList *list) {
    free(list->elements);
    list->elements = NULL;
    list->size = 0;
    list->capacity = 0;
}

int containsTuple(Tuple *tuples, int tupleCount, int value) {
    for (int i = 0; i < tupleCount; i++) {
        if (tuples[i].value == value) {
            return i;
        }
    }
    return -1;
}

int *extractSingles(Tuple *tuples, int tupleCount, int *resultSize) {
    if (resultSize == NULL) {
        return NULL;
    }

    if (tuples == NULL || tupleCount <= 0) {
        *resultSize = 0;
        return NULL;
    }

    Tuple *uniqueTuples = (Tuple *)malloc(tupleCount * sizeof(Tuple));
    if (uniqueTuples == NULL) {
        *resultSize = 0;
        return NULL;
    }

    int uniqueCount = 0;
    for (int i = 0; i < tupleCount; i++) {
        int index = containsTuple(uniqueTuples, uniqueCount, tuples[i].value);
        if (index == -1) {
            uniqueTuples[uniqueCount].value = tuples[i].value;
            uniqueTuples[uniqueCount].count = 1;
            uniqueCount++;
        } else {
            uniqueTuples[index].count++;
        }
    }

    IntList result;
    initList(&result);

    for (int i = 0; i < uniqueCount; i++) {
        if (uniqueTuples[i].count == 1) {
            if (!addElement(&result, uniqueTuples[i].value)) {
                free(uniqueTuples);
                freeList(&result);
                *resultSize = 0;
                return NULL;
            }
        }
    }

    free(uniqueTuples);

    if (result.size == 0) {
        freeList(&result);
        *resultSize = 0;
        return NULL;
    }

    *resultSize = result.size;
    return result.elements;
}

int main(void) {
    Tuple tuples[] = {
        {1, 1},
        {2, 1},
        {3, 1},
        {2, 1},
        {4, 1},
        {1, 1},
        {5, 1}
    };
    int tupleCount = sizeof(tuples) / sizeof(tuples[0]);
    int resultSize = 0;

    int *singles = extractSingles(tuples, tupleCount, &resultSize);

    if (singles != NULL) {
        printf("Elements occurring singly: ");
        for (int i = 0; i < resultSize; i++) {
            printf("%d ", singles[i]);
        }
        printf("\n");
        free(singles);
    } else {
        printf("No elements occurring singly or memory allocation failed.\n");
    }

    return 0;
}