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

typedef struct {
    int *elements;
    int size;
    int capacity;
} IntSet;

static void initIntSet(IntSet *set) {
    set->elements = NULL;
    set->size = 0;
    set->capacity = 0;
}

static void freeIntSet(IntSet *set) {
    free(set->elements);
    set->elements = NULL;
    set->size = 0;
    set->capacity = 0;
}

static int containsInt(IntSet *set, int value) {
    int i;
    for (i = 0; i < set->size; i++) {
        if (set->elements[i] == value) {
            return 1;
        }
    }
    return 0;
}

static int addInt(IntSet *set, int value) {
    if (containsInt(set, value)) {
        return 1;
    }
    if (set->size == set->capacity) {
        int newCapacity = set->capacity == 0 ? 8 : set->capacity * 2;
        int *newElements = (int *)realloc(set->elements, newCapacity * sizeof(int));
        if (newElements == NULL) {
            return 0;
        }
        set->elements = newElements;
        set->capacity = newCapacity;
    }
    set->elements[set->size] = value;
    set->size++;
    return 1;
}

static int compareInts(const void *a, const void *b) {
    int intA = *(const int *)a;
    int intB = *(const int *)b;
    return (intA > intB) - (intA < intB);
}

static int tupleContains(Tuple *tuple, int value) {
    int i;
    for (i = 0; i < tuple->size; i++) {
        if (tuple->elements[i] == value) {
            return 1;
        }
    }
    return 0;
}

Tuple tupleIntersection(TupleList *list) {
    Tuple result;
    IntSet candidateSet;
    IntSet resultSet;
    int i, j;

    result.elements = NULL;
    result.size = 0;

    if (list == NULL || list->count <= 0) {
        return result;
    }

    initIntSet(&candidateSet);
    initIntSet(&resultSet);

    for (i = 0; i < list->tuples[0].size; i++) {
        if (!addInt(&candidateSet, list->tuples[0].elements[i])) {
            freeIntSet(&candidateSet);
            freeIntSet(&resultSet);
            return result;
        }
    }

    for (i = 1; i < list->count; i++) {
        for (j = 0; j < candidateSet.size; j++) {
            if (tupleContains(&list->tuples[i], candidateSet.elements[j])) {
                if (!addInt(&resultSet, candidateSet.elements[j])) {
                    freeIntSet(&candidateSet);
                    freeIntSet(&resultSet);
                    return result;
                }
            }
        }
        freeIntSet(&candidateSet);
        candidateSet = resultSet;
        initIntSet(&resultSet);
    }

    result.size = candidateSet.size;
    if (result.size > 0) {
        result.elements = (int *)malloc(result.size * sizeof(int));
        if (result.elements == NULL) {
            freeIntSet(&candidateSet);
            return result;
        }
        memcpy(result.elements, candidateSet.elements, result.size * sizeof(int));
        qsort(result.elements, result.size, sizeof(int), compareInts);
    }

    freeIntSet(&candidateSet);
    freeIntSet(&resultSet);

    return result;
}

int main(void) {
    int tuple1Elements[] = {3, 1, 4, 2};
    int tuple2Elements[] = {2, 5, 3, 6};
    int tuple3Elements[] = {7, 3, 2, 8};

    Tuple tuple1 = {tuple1Elements, 4};
    Tuple tuple2 = {tuple2Elements, 4};
    Tuple tuple3 = {tuple3Elements, 4};

    Tuple tuples[] = {tuple1, tuple2, tuple3};
    TupleList list = {tuples, 3};

    Tuple intersection = tupleIntersection(&list);

    printf("Intersection: ");
    for (int i = 0; i < intersection.size; i++) {
        printf("%d ", intersection.elements[i]);
    }
    printf("\n");

    free(intersection.elements);

    return 0;
}