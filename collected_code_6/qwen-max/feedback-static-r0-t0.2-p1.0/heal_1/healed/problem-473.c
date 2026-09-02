#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

int compare(const void *a, const void *b) {
    return (*(const int*)a - *(const int*)b);
}

int isSubset(const int *a, int aSize, const int *b, int bSize) {
    int i = 0, j = 0;
    while (i < aSize && j < bSize) {
        if (a[i] == b[j]) {
            i++;
            j++;
        } else if (a[i] < b[j]) {
            i++;
        } else {
            j++;
        }
    }
    return i == aSize;
}

Tuple* findIntersection(Tuple *tuples, int n, int *returnSize) {
    for (int i = 0; i < n; i++) {
        qsort(tuples[i].elements, tuples[i].size, sizeof(int), compare);
    }

    *returnSize = 0;
    int *intersection = (int *)malloc(n * sizeof(int));
    if (!intersection) {
        return NULL;
    }

    for (int i = 0; i < tuples[0].size; i++) {
        int element = tuples[0].elements[i];
        int foundInAll = 1;
        for (int j = 1; j < n; j++) {
            if (!isSubset(&element, 1, tuples[j].elements, tuples[j].size)) {
                foundInAll = 0;
                break;
            }
        }
        if (foundInAll) {
            intersection[(*returnSize)++] = element;
        }
    }

    Tuple *result = (Tuple *)malloc(sizeof(Tuple));
    if (!result) {
        free(intersection);
        return NULL;
    }
    result->elements = intersection;
    result->size = *returnSize;
    return result;
}

int main() {
    Tuple tuples[] = {
        { .elements = (int[]){3, 1, 2}, .size = 3 },
        { .elements = (int[]){2, 3, 1}, .size = 3 },
        { .elements = (int[]){1, 2, 3, 4}, .size = 4 }
    };
    int n = sizeof(tuples) / sizeof(tuples[0]);
    int returnSize;
    Tuple *result = findIntersection(tuples, n, &returnSize);

    if (result) {
        for (int i = 0; i < result->size; i++) {
            printf("%d ", result->elements[i]);
        }
        free(result->elements);
        free(result);
    }

    return 0;
}