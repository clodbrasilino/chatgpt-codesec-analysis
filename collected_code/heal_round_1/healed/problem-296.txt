#include <stdio.h>

int countInversions(const int arr[], int n) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    const int arr[] = {5, 2, 8, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    int inversions = countInversions(arr, n);
    printf("Number of inversions: %d\n", inversions);

    return 0;
}