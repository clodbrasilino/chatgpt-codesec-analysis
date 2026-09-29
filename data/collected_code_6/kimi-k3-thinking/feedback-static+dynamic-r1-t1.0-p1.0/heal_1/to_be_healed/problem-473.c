#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    const int *items;
    size_t length;
} IntTuple;

static int arrayContains(const int *array, size_t length, int value)
{
    size_t i;

    if (array == NULL) {
        return 0;
    }

    for (i = 0; i < length; ++i) {
        if (array[i] == value) {
            return 1;
        }
    }

    return 0;
}

size_t tupleIntersection(const IntTuple *tuples, size_t tupleCount, int **outResult)
{
    int *result;
    int *resized;
    size_t resultSize;
    size_t i;
    size_t j;
    /* Possible weaknesses found:
     *  The scope of the variable 'candidate' can be reduced. [variableScope]
     */
    int candidate;
    /* Possible weaknesses found:
     *  The scope of the variable 'presentInAll' can be reduced. [variableScope]
     */
    int presentInAll;

    if (outResult == NULL) {
        return 0;
    }
    *outResult = NULL;

    if (tuples == NULL || tupleCount == 0 ||
        tuples[0].items == NULL || tuples[0].length == 0) {
        return 0;
    }

    if (tuples[0].length > SIZE_MAX / sizeof(int)) {
        return 0;
    }

    result = malloc(tuples[0].length * sizeof(*result));
    if (result == NULL) {
        return 0;
    }

    resultSize = 0;
    for (i = 0; i < tuples[0].length; ++i) {
        candidate = tuples[0].items[i];
        presentInAll = 1;

        if (arrayContains(result, resultSize, candidate)) {
            continue;
        }

        for (j = 1; j < tupleCount; ++j) {
            if (!arrayContains(tuples[j].items, tuples[j].length, candidate)) {
                presentInAll = 0;
                break;
            }
        }

        if (presentInAll) {
            result[resultSize] = candidate;
            ++resultSize;
        }
    }

    if (resultSize == 0) {
        free(result);
        return 0;
    }

    resized = realloc(result, resultSize * sizeof(*resized));
    if (resized != NULL) {
        result = resized;
    }

    *outResult = result;
    return resultSize;
}

static void printIntersection(const char *label, const int *values, size_t count)
{
    size_t i;

    printf("%s: (", label);
    for (i = 0; values != NULL && i < count; ++i) {
        printf("%d", values[i]);
        if (i + 1 < count) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void)
{
    int data1[] = {3, 4};
    int data2[] = {5, 6};
    int data3[] = {9, 10};
    int data4[] = {4, 5};
    IntTuple tupleList1[] = {
        {data1, 2},
        {data2, 2},
        {data3, 2},
        {data4, 2}
    };

    int data5[] = {4, 1};
    int data6[] = {3, 4, 5};
    int data7[] = {4, 6};
    IntTuple tupleList2[] = {
        {data5, 2},
        {data6, 3},
        {data7, 2}
    };

    int *intersection;
    size_t intersectionSize;

    intersection = NULL;
    intersectionSize = tupleIntersection(tupleList1,
                                         sizeof(tupleList1) / sizeof(tupleList1[0]),
                                         &intersection);
    printIntersection("Intersection of list 1", intersection, intersectionSize);
    free(intersection);
    intersection = NULL;

    intersectionSize = tupleIntersection(tupleList2,
                                         sizeof(tupleList2) / sizeof(tupleList2[0]),
                                         &intersection);
    printIntersection("Intersection of list 2", intersection, intersectionSize);
    free(intersection);
    intersection = NULL;

    return 0;
}