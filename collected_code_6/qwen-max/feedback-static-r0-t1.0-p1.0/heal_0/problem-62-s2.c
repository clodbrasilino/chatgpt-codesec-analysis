#include <stdio.h>
#include <limits.h>

int find_smallest(int *arr, int n) {
    if (n <= 0) return INT_MAX;
    int smallest = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] < smallest) {
            smallest = arr[i];
        }
    }
    return smallest;
}

int main() {
    int arr[] = {5, 3, 9, 1, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int smallest = find_smallest(arr, n);
    printf("Smallest number: %d\n", smallest);
    return 0;
}