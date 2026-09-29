#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

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
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'INT_MIN'
     *  'INT_MAX' undeclared (first use in this function)
     *  'INT_MIN' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     */
    int currentMin = INT_MAX, currentMax = INT_MIN;
    for (int i = 0; i < K; i++) {
        if (elements[i].value < currentMin) currentMin = elements[i].value;
        if (elements[i].value > currentMax) currentMax = elements[i].value;
    }

    int bestStart = currentMin;
    int bestEnd = currentMax;

    while (1) {
        int minIndex = 0, maxIndex = 0;
        for (int i = 1; i < K; i++) {
            if (elements[i].value < elements[minIndex].value) minIndex = i;
            if (elements[i].value > elements[maxIndex].value) maxIndex = i;
        }

        /* Possible weaknesses found:
         *  Uninitialized variables: elements.value, elements.index
         *  Uninitialized variables: elements.value, elements.index [uninitvar]
         */
        if (bestEnd - bestStart > elements[maxIndex].value - elements[minIndex].value) {
            bestStart = elements[minIndex].value;
            bestEnd = elements[maxIndex].value;
        }

        if (elements[minIndex].index + 1 < size[minIndex]) {
            elements[minIndex].index++;
            elements[minIndex].value = arr[minIndex][elements[minIndex].index];
            qsort(elements, K, sizeof(Element), compare);
        } else {
            break;
        }
    }

    *minRange = bestEnd - bestStart;
    *start = bestStart;
    *end = bestEnd;
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