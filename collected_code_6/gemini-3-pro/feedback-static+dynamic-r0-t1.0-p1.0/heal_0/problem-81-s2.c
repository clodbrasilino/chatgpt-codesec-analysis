#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr1;
    int *arr2;
    int size;
} TuplePair;

typedef struct {
    int first;
    int second;
} ZippedTuple;

ZippedTuple* zip_tuples(const TuplePair *pair) {
    if (pair == NULL || pair->arr1 == NULL || pair->arr2 == NULL || pair->size <= 0) {
        return NULL;
    }

    ZippedTuple *zipped = (ZippedTuple*)malloc(pair->size * sizeof(ZippedTuple));
    if (zipped == NULL) {
        return NULL;
    }

    for (int i = 0; i < pair->size; i++) {
        zipped[i].first = pair->arr1[i];
        zipped[i].second = pair->arr2[i];
    }

    return zipped;
}

int main() {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};
    
    TuplePair pair;
    pair.arr1 = arr1;
    pair.arr2 = arr2;
    pair.size = sizeof(arr1) / sizeof(arr1[0]);

    ZippedTuple *result = zip_tuples(&pair);
    
    if (result != NULL) {
        for (int i = 0; i < pair.size; i++) {
            printf("(%d, %d)\n", result[i].first, result[i].second);
        }
        free(result);
    } else {
        printf("Failed to zip tuples.\n");
    }

    return 0;
}