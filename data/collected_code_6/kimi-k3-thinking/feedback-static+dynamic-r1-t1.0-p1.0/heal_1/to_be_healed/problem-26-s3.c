#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

static bool tupleListHasAllKElements(const TupleList *list, size_t k)
{
    size_t i;

    if (list == NULL) {
        return false;
    }
    if (list->count > 0 && list->tuples == NULL) {
        return false;
    }
    for (i = 0; i < list->count; i++) {
        if (list->tuples[i].length != k) {
            return false;
        }
        if (list->tuples[i].length > 0 && list->tuples[i].data == NULL) {
            return false;
        }
    }
    return true;
}

static bool initTuple(Tuple *tuple, const int *values, size_t length)
{
    size_t i;

    if (tuple == NULL) {
        return false;
    }
    tuple->data = NULL;
    tuple->length = 0;
    if (length == 0) {
        return true;
    }
    if (values == NULL) {
        return false;
    }
    if (length > SIZE_MAX / sizeof(int)) {
        return false;
    }
    tuple->data = (int *)malloc(length * sizeof(int));
    if (tuple->data == NULL) {
        return false;
    }
    for (i = 0; i < length; i++) {
        tuple->data[i] = values[i];
    }
    tuple->length = length;
    return true;
}

static void freeTuple(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }
    free(tuple->data);
    tuple->data = NULL;
    tuple->length = 0;
}

static void freeTupleList(TupleList *list)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (list == NULL) {
        return;
    }
    if (list->tuples != NULL) {
        for (i = 0; i < list->count; i++) {
            freeTuple(&list->tuples[i]);
        }
        free(list->tuples);
        list->tuples = NULL;
    }
    list->count = 0;
}

int main(void)
{
    TupleList list;
    /* Possible weaknesses found:
     *  Variable 'values1' can be declared as const array [constVariable]
     */
    int values1[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'values2' can be declared as const array [constVariable]
     */
    int values2[] = {4, 5, 6};
    /* Possible weaknesses found:
     *  Variable 'values3' can be declared as const array [constVariable]
     */
    int values3[] = {7, 8, 9};
    /* Possible weaknesses found:
     *  The scope of the variable 'k' can be reduced. [variableScope]
     */
    size_t k = 3;
    size_t i;
    bool ok = true;

    list.tuples = NULL;
    list.count = 0;

    list.tuples = (Tuple *)malloc(3 * sizeof(Tuple));
    if (list.tuples == NULL) {
        return EXIT_FAILURE;
    }
    list.count = 3;

    for (i = 0; i < list.count; i++) {
        list.tuples[i].data = NULL;
        list.tuples[i].length = 0;
    }

    if (!initTuple(&list.tuples[0], values1, 3) ||
        !initTuple(&list.tuples[1], values2, 3) ||
        !initTuple(&list.tuples[2], values3, 3)) {
        ok = false;
    }

    if (ok) {
        if (tupleListHasAllKElements(&list, k)) {
            printf("All tuples have %zu elements.\n", k);
        } else {
            printf("Not all tuples have %zu elements.\n", k);
        }
        if (tupleListHasAllKElements(&list, 4)) {
            printf("All tuples have %d elements.\n", 4);
        } else {
            printf("Not all tuples have %d elements.\n", 4);
        }
    } else {
        printf("Failed to build the tuple list.\n");
    }

    freeTupleList(&list);

    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}