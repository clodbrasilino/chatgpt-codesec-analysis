#include <stdio.h>
#include <limits.h>

int min_sublist_length(int *arr, int n) {
    if (n == 0) {
        return 0;
    }

    int min_length = INT_MAX;
    for (int i = 0; i < n; ++i) {
        int max_val = arr[i];
        int min_val = arr[i];

        for (int j = i; j < n; ++j) {
            max_val = max_val > arr[j] ? max_val : arr[j];
            min_val = min_val < arr[j] ? min_val : arr[j];
            if (max_val - min_val == j - i) {
                min_length = min_length < (j - i + 1) ? min_length : (j - i + 1);
                break;
            }
        }
    }
    return min_length < INT_MAX ? min_length : 0;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = min_sublist_length(arr, n);
    printf("Minimum sublist length: %d\n", result);
    return 0;
}