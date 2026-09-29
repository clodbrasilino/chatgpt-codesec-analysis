#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void findKPairs(int* arr1, int size1, int* arr2, int size2, int k, Pair* result) {
    qsort(arr1, size1, sizeof(int), compare);
    qsort(arr2, size2, sizeof(int), compare);

    int i = 0, j = 0, count = 0;
    while (i < size1 && j < size2 && count < k) {
        result[count].first = arr1[i];
        result[count].second = arr2[j];
        if (i == size1 - 1 || (j + 1 < size2 && arr1[i] > arr2[j + 1])) {
            j++;
        } else {
            i++;
        }
        count++;
    }
}

int main() {
    int arr1[] = {1, 3, 11};
    int arr2[] = {2, 4, 8};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int k = 4;
    Pair result[k];

    findKPairs(arr1, size1, arr2, size2, k, result);

    for (int i = 0; i < k; i++) {
        printf("(%d, %d)\n", result[i].first, result[i].second);
    }

    return 0;
}