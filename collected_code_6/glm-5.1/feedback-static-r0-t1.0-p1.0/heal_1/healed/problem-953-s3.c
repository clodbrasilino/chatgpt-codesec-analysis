#include <stdio.h>
#include <stdlib.h>

int find_min_subsets(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    int *counts = (int *)calloc(1001, sizeof(int));
    if (counts == NULL) {
        exit(EXIT_FAILURE);
    }

    int max_count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0 && arr[i] <= 1000) {
            counts[arr[i]]++;
            if (counts[arr[i]] > max_count) {
                max_count = counts[arr[i]];
            }
        }
    }

    free(counts);
    return max_count;
}

int main() {
    int arr1[] = {1, 2, 3, 4};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = find_min_subsets(arr1, n1);
    printf("%d\n", result1);

    int arr2[] = {1, 2, 3, 1, 2, 3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = find_min_subsets(arr2, n2);
    printf("%d\n", result2);

    int arr3[] = {5, 5, 5, 5, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int result3 = find_min_subsets(arr3, n3);
    printf("%d\n", result3);

    const int *arr4 = NULL;
    int result4 = find_min_subsets(arr4, 0);
    printf("%d\n", result4);

    return 0;
}