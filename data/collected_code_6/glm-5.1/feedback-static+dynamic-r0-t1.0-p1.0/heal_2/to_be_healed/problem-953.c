#include <stdio.h>
#include <stdlib.h>

int find_min_subsets(const int *arr, int n) {
    if (n <= 0) {
        return 0;
    }

    int max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    int size = max_val + 1;
    int *count = (int *)calloc(size, sizeof(int));
    if (count == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    int max_count = 0;
    for (int i = 0; i < size; i++) {
        if (count[i] > max_count) {
            max_count = count[i];
        }
    }

    free(count);

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

    /* Possible weaknesses found:
     *  Variable 'arr4' can be declared as const array [constVariable]
     */
    int arr4[] = {};
    int n4 = 0;
    int result4 = find_min_subsets(arr4, n4);
    printf("%d\n", result4);

    return 0;
}