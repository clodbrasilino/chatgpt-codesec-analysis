#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(const int *)a - *(const int *)b);
}

int min_subsets_with_distinct_elements(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    int *sorted = (int *)malloc(n * sizeof(int));
    if (sorted == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }

    qsort(sorted, n, sizeof(int), compare);

    int max_freq = 1;
    int current_freq = 1;

    for (int i = 1; i < n; i++) {
        if (sorted[i] == sorted[i - 1]) {
            current_freq++;
        } else {
            if (current_freq > max_freq) {
                max_freq = current_freq;
            }
            current_freq = 1;
        }
    }

    if (current_freq > max_freq) {
        max_freq = current_freq;
    }

    free(sorted);
    return max_freq;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", min_subsets_with_distinct_elements(arr1, n1));

    int arr2[] = {1, 2, 1, 2, 3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", min_subsets_with_distinct_elements(arr2, n2));

    int arr3[] = {1, 1, 1, 1, 1};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", min_subsets_with_distinct_elements(arr3, n3));

    int arr4[] = {};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%d\n", min_subsets_with_distinct_elements(arr4, n4));

    const int *arr5 = NULL;
    printf("%d\n", min_subsets_with_distinct_elements(arr5, 5));

    return 0;
}