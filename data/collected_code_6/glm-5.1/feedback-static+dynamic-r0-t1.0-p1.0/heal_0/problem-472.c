#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

bool areConsecutive(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return false;
    }

    if (n == 1) {
        return true;
    }

    int min_val = INT_MAX;
    int max_val = INT_MIN;
    long long sum = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
        sum += arr[i];
    }

    if ((max_val - min_val + 1) != n) {
        return false;
    }

    if ((long long)max_val * ((long long)max_val + 1) / 2 - (long long)(min_val - 1) * (long long)min_val / 2 != sum) {
        return false;
    }

    bool *visited = (bool *)calloc(n, sizeof(bool));
    if (visited == NULL) {
        return false;
    }

    for (int i = 0; i < n; i++) {
        int idx = arr[i] - min_val;
        if (idx < 0 || idx >= n || visited[idx]) {
            free(visited);
            return false;
        }
        visited[idx] = true;
    }

    free(visited);
    return true;
}

int main() {
    int arr1[] = {5, 2, 3, 1, 4};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", areConsecutive(arr1, n1));

    int arr2[] = {5, 2, 3, 1, 6};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", areConsecutive(arr2, n2));

    int arr3[] = {5, 2, 3, 1, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", areConsecutive(arr3, n3));

    int *arr4 = NULL;
    int n4 = 0;
    printf("%d\n", areConsecutive(arr4, n4));

    return 0;
}