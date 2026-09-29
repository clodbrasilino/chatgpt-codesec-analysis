#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int findIntersection(int *arr1, int size1, int *arr2, int size2, int **result) {
    qsort(arr1, size1, sizeof(int), compare);
    qsort(arr2, size2, sizeof(int), compare);

    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (arr1[i] < arr2[j]) {
            i++;
        } else if (arr2[j] < arr1[i]) {
            j++;
        } else {
            (*result)[k++] = arr1[i++];
            j++;
        }
    }

    return k;
}

int main() {
    int arr1[] = {4, 9, 5, 1, 3};
    int arr2[] = {9, 4, 2, 6, 5};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);

    int *result = (int *)malloc((size1 + size2) * sizeof(int));
    if (result == NULL) {
        return 1;
    }

    int resultSize = findIntersection(arr1, size1, arr2, size2, &result);

    for (int i = 0; i < resultSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}