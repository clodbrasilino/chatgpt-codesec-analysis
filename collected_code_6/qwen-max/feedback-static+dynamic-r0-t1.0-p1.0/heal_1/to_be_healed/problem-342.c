#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int index;
} Element;

int compare(const void *a, const void *b) {
    return ((Element *)a)->value - ((Element *)b)->value;
}

/* Possible weaknesses found:
 *  Parameter 'size' can be declared as const array [constParameter]
 */
void findSmallestRange(int **arr, int K, int size[], int *minRange, int *start, int *end) {
    /* Possible weaknesses found:
     *  Variable 'N' is assigned a value that is never used. [unreadVariable]
     */
    int N = size[0];
    /* Possible weaknesses found:
     *  variable-sized object may not be initialized except with an empty initializer
     *  variable-sized object may not be initialized
     */
    Element elements[K] = {0};

    for (int i = 0; i < K; i++) {
        elements[i].value = arr[i][0];
        elements[i].index = 0;
    }

    int currentMin = elements[0].value;
    int currentMax = elements[0].value;
    for (int i = 1; i < K; i++) {
        if (elements[i].value < currentMin) currentMin = elements[i].value;
        if (elements[i].value > currentMax) currentMax = elements[i].value;
    }

    int currentStart = currentMin;
    int currentEnd = currentMax;

    while (1) {
        int minIndex = 0, maxIndex = 0;
        for (int i = 1; i < K; i++) {
            if (elements[i].value < elements[minIndex].value) minIndex = i;
            if (elements[i].value > elements[maxIndex].value) maxIndex = i;
        }

        if (currentEnd - currentStart > elements[maxIndex].value - elements[minIndex].value) {
            currentStart = elements[minIndex].value;
            currentEnd = elements[maxIndex].value;
        }

        if (elements[minIndex].index + 1 < size[minIndex]) {
            elements[minIndex].index++;
            elements[minIndex].value = arr[minIndex][elements[minIndex].index];

            qsort(elements, K, sizeof(Element), compare);
            /* Possible weaknesses found:
             *  Variable 'currentMin' is assigned a value that is never used. [unreadVariable]
             */
            currentMin = elements[0].value;
            /* Possible weaknesses found:
             *  Variable 'currentMax' is assigned a value that is never used. [unreadVariable]
             */
            currentMax = elements[K-1].value;
        } else {
            break;
        }
    }

    *minRange = currentEnd - currentStart;
    *start = currentStart;
    *end = currentEnd;
}

int main() {
    int arr[][4] = {{1, 2, 3, 4}, {2, 3, 4, 5}, {1, 2, 3, 4}};
    int K = 3;
    int size[] = {4, 4, 4};
    int minRange, start, end;

    findSmallestRange((int **)arr, K, size, &minRange, &start, &end);

    printf("The smallest range is [%d, %d]\n", start, end);
    return 0;
}