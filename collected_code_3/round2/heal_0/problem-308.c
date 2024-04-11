#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

void findLargestProducts(int* arr1, int* arr2, int n, int k) {
    qsort(arr1, n, sizeof(int), compare);
    qsort(arr2, n, sizeof(int), compare);

    int index1 = 0, index2 = 0;

    for (int i = 0; i < k; i++) {
        printf("%d ", arr1[index1] * arr2[index2]);

        if (index1 != n - 1 && index2 != n - 1) {
            if (arr1[index1 + 1] * arr2[index2] > arr1[index1] * arr2[index2 + 1]) {
                index1++;
            } else {
                index2++;
            }
        } else if (index1 != n - 1) {
            index1++;
        } else if (index2 != n - 1) {
            index2++;
        }
    }
}

int main() {
    int arr1[] = {1, 7, 9, 3, 2};
    int arr2[] = {4, 5, 8, 2, 1};
    int n = sizeof(arr1) / sizeof(arr1[0]);
    int k = 3;

    findLargestProducts(arr1, arr2, n, k);

    return 0;
}