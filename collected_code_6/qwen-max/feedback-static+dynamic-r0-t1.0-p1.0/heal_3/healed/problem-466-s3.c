#include <stdio.h>

int find_peak(const int *arr, int n) {
    if (n == 0) return -1;
    if (n == 1) return 0;

    for (int i = 1; i < n - 1; i++) {
        if (arr[i] >= arr[i - 1] && arr[i] >= arr[i + 1]) {
            return i;
        }
    }

    if (arr[0] >= arr[1]) return 0;
    if (arr[n - 1] >= arr[n - 2]) return n - 1;

    return -1;
}

int main() {
    int arr[] = {1, 3, 20, 4, 1, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    int peak_index = find_peak(arr, n);
    if (peak_index != -1) {
        printf("Peak element is: %d\n", arr[peak_index]);
    } else {
        printf("No peak element found.\n");
    }
    return 0;
}