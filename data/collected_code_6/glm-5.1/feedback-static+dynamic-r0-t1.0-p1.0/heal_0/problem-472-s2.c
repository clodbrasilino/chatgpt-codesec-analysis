#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

bool are_consecutive(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return false;
    }

    if (n == 1) {
        return true;
    }

    int min_val = INT_MAX;
    int max_val = INT_MIN;

    for (int i = 0; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    if (max_val - min_val + 1 != n) {
        return false;
    }

    bool *visited = (bool *)calloc(n, sizeof(bool));
    if (visited == NULL) {
        return false;
    }

    bool result = true;

    for (int i = 0; i < n; i++) {
        int idx = arr[i] - min_val;
        if (idx < 0 || idx >= n || visited[idx]) {
            result = false;
            break;
        }
        visited[idx] = true;
    }

    free(visited);
    return result;
}

int main() {
    int arr1[] = {5, 2, 3, 1, 4};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    int arr2[] = {5, 2, 3, 1, 4, 8};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    int arr3[] = {1, 2, 3, 4, 5, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    int *arr4 = NULL;
    int n4 = 0;

    int arr5[] = {7};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);

    printf("%d\n", are_consecutive(arr1, n1));
    printf("%d\n", are_consecutive(arr2, n2));
    printf("%d\n", are_consecutive(arr3, n3));
    printf("%d\n", are_consecutive(arr4, n4));
    printf("%d\n", are_consecutive(arr5, n5));

    return 0;
}