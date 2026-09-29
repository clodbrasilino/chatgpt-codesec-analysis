#include <stdio.h>
#include <limits.h>

int find_second_smallest(const int arr[], int n) {
    int smallest = INT_MAX, second_smallest = INT_MAX;
    for (int i = 0; i < n; ++i) {
        if (arr[i] < smallest) {
            second_smallest = smallest;
            smallest = arr[i];
        } else if (arr[i] < second_smallest && arr[i] != smallest) {
            second_smallest = arr[i];
        }
    }
    return second_smallest == INT_MAX ? -1 : second_smallest;
}

int main() {
    const int arr[] = {4, 2, 1, 3, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = find_second_smallest(arr, n);
    if (result != -1) {
        printf("Second smallest element is: %d\n", result);
    } else {
        printf("No second smallest element found.\n");
    }
    return 0;
}