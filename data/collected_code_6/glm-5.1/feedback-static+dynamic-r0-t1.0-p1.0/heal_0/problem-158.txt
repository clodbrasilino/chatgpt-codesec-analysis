#include <stdio.h>
#include <stdlib.h>

int find_k_operations(int *arr, int n, int target) {
    int operations = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > target) {
            operations += arr[i] - target;
        } else {
            operations += target - arr[i];
        }
    }
    return operations;
}

int compare(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int find_min_operations(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }
    qsort(arr, n, sizeof(int), compare);
    int median = arr[n / 2];
    return find_k_operations(arr, n, median);
}

int main() {
    int arr1[] = {1, 2, 3};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int res1 = find_min_operations(arr1, n1);
    printf("%d\n", res1);

    int arr2[] = {10, 20, 30, 40};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int res2 = find_min_operations(arr2, n2);
    printf("%d\n", res2);

    int arr3[] = {5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int res3 = find_min_operations(arr3, n3);
    printf("%d\n", res3);

    return 0;
}