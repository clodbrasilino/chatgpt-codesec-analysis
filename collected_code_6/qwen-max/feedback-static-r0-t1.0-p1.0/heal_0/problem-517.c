#include <stdio.h>
#include <limits.h>

int find_largest_positive(int *arr, int n) {
    int largest = INT_MIN;
    for (int i = 0; i < n; ++i) {
        if (arr[i] > 0 && arr[i] > largest) {
            largest = arr[i];
        }
    }
    return largest;
}

int main() {
    int arr[] = {3, -1, 7, 15, -9, 22, 0, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int max_positive = find_largest_positive(arr, n);
    if (max_positive != INT_MIN) {
        printf("Largest positive number: %d\n", max_positive);
    } else {
        printf("No positive numbers found.\n");
    }
    return 0;
}