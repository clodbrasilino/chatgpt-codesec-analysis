#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int arr1;
    int arr2;
} Pair;

int cmpfunc(const void * a, const void * b) {
    return (*(int*)a - *(int*)b);
}

void findKPairs(int *arr1, int len1, int *arr2, int len2, int k, Pair *result) {
    qsort(arr1, len1, sizeof(int), cmpfunc);
    qsort(arr2, len2, sizeof(int), cmpfunc);

    int index1 = 0, index2 = 0;
    for (int i = 0; i < k && index1 < len1 && index2 < len2; ++i) {
        result[i].arr1 = arr1[index1];
        result[i].arr2 = arr2[index2];
        if (index1 + 1 == len1 || (index2 + 1 < len2 && arr1[index1 + 1] > arr2[index2 + 1])) {
            index2++;
        } else {
            index1++;
        }
    }
}

int main() {
    int arr1[] = {1, 3, 5};
    int len1 = sizeof(arr1) / sizeof(arr1[0]);
    int arr2[] = {2, 4, 6};
    int len2 = sizeof(arr2) / sizeof(arr2[0]);
    int k = 4;
    Pair result[k];

    findKPairs(arr1, len1, arr2, len2, k, result);

    for (int i = 0; i < k; ++i) {
        printf("(%d, %d) ", result[i].arr1, result[i].arr2);
    }

    return 0;
}