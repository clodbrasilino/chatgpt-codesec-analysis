#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int find_min_subsets(int *arr, int n) {
    if (n == 0) return 0;

    qsort(arr, n, sizeof(int), compare);

    int count = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] != arr[i - 1]) {
            count++;
        }
    }

    return (n + count - 1) / count;
}

int main() {
    int arr1[] = {1, 2, 2, 3, 4};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", find_min_subsets(arr1, n1));

    int arr2[] = {5, 6, 7, 8, 9};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", find_min_subsets(arr2, n2));

    int arr3[] = {10, 10, 10};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", find_min_subsets(arr3, n3));

    return 0;
}