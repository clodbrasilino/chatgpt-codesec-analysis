#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int index;
} Element;

int compare(const void *a, const void *b) {
    return ((Element *)a)->value - ((Element *)b)->value;
}

void findSmallestRange(int **arr, int K, const int size[], int *minRange, int *start, int *end) {
    Element elements[K];

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = 0; i < K; i++) {
        elements[i].value = arr[i][0];
        elements[i].index = 0;
    }

    /* Possible weaknesses found:
     *  Uninitialized variables: elements.value, elements.index [uninitvar]
     *  Same expression used in consecutive assignments of 'currentMin' and 'currentMax'.
     *  Same expression used in consecutive assignments of 'currentMin' and 'currentMax'. [duplicateAssignExpression]
     *  Uninitialized variables: elements.value, elements.index
     */
    int currentMin = elements[0].value;
    /* Possible weaknesses found:
     *  Same expression used in consecutive assignments of 'currentMin' and 'currentMax'.
     */
    int currentMax = elements[0].value;
    for (int i = 1; i < K; i++) {
        if (elements[i].value < currentMin) currentMin = elements[i].value;
        if (elements[i].value > currentMax) currentMax = elements[i].value;
    }

    int globalMinRange = currentMax - currentMin;
    *start = currentMin;
    *end = currentMax;

    while (1) {
        int minIndex = 0, maxIndex = 0;
        for (int i = 1; i < K; i++) {
            if (elements[i].value < elements[minIndex].value) minIndex = i;
            if (elements[i].value > elements[maxIndex].value) maxIndex = i;
        }

        int currentRange = elements[maxIndex].value - elements[minIndex].value;
        if (currentRange < globalMinRange) {
            *start = elements[minIndex].value;
            *end = elements[maxIndex].value;
            globalMinRange = currentRange;
        }

        if (elements[minIndex].index + 1 < size[minIndex]) {
            elements[minIndex].index++;
            elements[minIndex].value = arr[minIndex][elements[minIndex].index];
            qsort(elements, K, sizeof(Element), compare);
        } else {
            break;
        }
    }

    *minRange = globalMinRange;
}

int main() {
    int arr[][4] = {{1, 2, 3, 4}, {2, 3, 4, 5}, {1, 2, 3, 4}};
    int K = 3;
    int size[] = {4, 4, 4};
    int minRange, start, end;

    int *arr_pointers[3];
    for (int i = 0; i < K; ++i) {
        arr_pointers[i] = arr[i];
    }

    findSmallestRange(arr_pointers, K, size, &minRange, &start, &end);

    printf("The smallest range is [%d, %d]\n", start, end);
    return 0;
}