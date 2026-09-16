#include <stdio.h>
#include <limits.h>

int findMinSublistLength(int *arr, int n) {
    int min_length = INT_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int length = j - i + 1;
            if (length < min_length) {
                min_length = length;
            }
        }
    }
    return min_length == INT_MAX ? 0 : min_length;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int min_length = findMinSublistLength(arr, n);
    printf("Minimum sublist length: %d\n", min_length);
    return 0;
}