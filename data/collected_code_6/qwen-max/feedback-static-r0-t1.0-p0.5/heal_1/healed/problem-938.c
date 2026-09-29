#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void findThreeClosest(int *arr1, int size1, int *arr2, int size2, int *arr3, int size3) {
    int i = 0, j = 0, k = 0;
    int min_diff = INT_MAX;
    int res_i = 0, res_j = 0, res_k = 0;

    while (i < size1 && j < size2 && k < size3) {
        int max_val = (arr1[i] > arr2[j]) ? ((arr1[i] > arr3[k]) ? arr1[i] : arr3[k]) : ((arr2[j] > arr3[k]) ? arr2[j] : arr3[k]);
        int min_val = (arr1[i] < arr2[j]) ? ((arr1[i] < arr3[k]) ? arr1[i] : arr3[k]) : ((arr2[j] < arr3[k]) ? arr2[j] : arr3[k]);

        if (max_val - min_val < min_diff) {
            min_diff = max_val - min_val;
            res_i = i;
            res_j = j;
            res_k = k;
        }

        if (arr1[i] == min_val) i++;
        else if (arr2[j] == min_val) j++;
        else k++;
    }

    printf("The three closest elements are: %d, %d, %d\n", arr1[res_i], arr2[res_j], arr3[res_k]);
}

int main() {
    int arr1[] = {1, 4, 10};
    int arr2[] = {2, 15, 20};
    int arr3[] = {10, 12};

    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int size3 = sizeof(arr3) / sizeof(arr3[0]);

    findThreeClosest(arr1, size1, arr2, size2, arr3, size3);

    return 0;
}