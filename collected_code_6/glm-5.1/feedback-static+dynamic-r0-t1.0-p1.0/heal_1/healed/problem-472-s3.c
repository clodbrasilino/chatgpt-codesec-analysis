#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

bool hasConsecutiveNumbers(const int *arr, int n) {
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

    bool *visited = (bool *)malloc(n * sizeof(bool));
    if (visited == NULL) {
        return false;
    }

    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    for (int i = 0; i < n; i++) {
        int index = arr[i] - min_val;
        if (index < 0 || index >= n || visited[index]) {
            free(visited);
            return false;
        }
        visited[index] = true;
    }

    free(visited);
    return true;
}

int main() {
    int arr1[] = {5, 2, 3, 1, 4};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", hasConsecutiveNumbers(arr1, n1));

    int arr2[] = {5, 2, 3, 1, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", hasConsecutiveNumbers(arr2, n2));

    int arr3[] = {1, 2, 4, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", hasConsecutiveNumbers(arr3, n3));

    printf("%d\n", hasConsecutiveNumbers(NULL, 5));

    return 0;
}