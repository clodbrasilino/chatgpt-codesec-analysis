#include <stdio.h>

int find_peak_element(const int arr[], int n) {
    if (n == 0) return -1;
    for (int i = 0; i < n; i++) {
        if ((i == 0 || arr[i] >= arr[i-1]) && (i == n-1 || arr[i] >= arr[i+1])) {
            return i;
        }
    }
    return -1;
}

int main() {
    const int arr[] = {1, 3, 20, 4, 1, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    int peak_index = find_peak_element(arr, n);
    if (peak_index != -1) {
        printf("Peak element is %d at index %d\n", arr[peak_index], peak_index);
    } else {
        printf("No peak element found\n");
    }
    return 0;
}