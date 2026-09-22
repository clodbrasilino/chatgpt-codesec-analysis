#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isElementInSet(const int* set, size_t setSize, int element) {
    if (set == NULL) {
        return false;
    }
    for (size_t i = 0; i < setSize; ++i) {
        if (set[i] == element) {
            return true;
        }
    }
    return false;
}

int* tupleToSet(const int* tupleElements, size_t numElements, size_t* outSetSize) {
    if (tupleElements == NULL || outSetSize == NULL) {
        return NULL;
    }

    if (numElements == 0) {
        *outSetSize = 0;
        return NULL;
    }

    int* set = (int*)malloc(numElements * sizeof(int));
    if (set == NULL) {
        *outSetSize = 0;
        return NULL;
    }

    size_t uniqueCount = 0;
    for (size_t i = 0; i < numElements; ++i) {
        if (!isElementInSet(set, uniqueCount, tupleElements[i])) {
            set[uniqueCount] = tupleElements[i];
            uniqueCount++;
        }
    }

    *outSetSize = uniqueCount;
    return set;
}

int main(void) {
    int tuples[] = {1, 2, 3, 2, 4, 1, 5, 3, 6, 4, 7};
    size_t numElements = sizeof(tuples) / sizeof(tuples[0]);
    size_t setSize = 0;

    int* mySet = tupleToSet(tuples, numElements, &setSize);
    
    if (mySet == NULL && numElements > 0) {
        fprintf(stderr, "Error: Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < setSize; ++i) {
        printf("%d ", mySet[i]);
    }
    printf("\n");

    free(mySet);
    mySet = NULL;

    return EXIT_SUCCESS;
}