#include <stdio.h>
#include <limits.h>

int find_max_difference(int arr[], int n) {
    int max_diff = arr[1] - arr[0];
    int min_element = arr[0];
    int i;
    for(i = 1; i < n; i++) {
        if (arr[i] - min_element > max_diff) {
            max_diff = arr[i] - min_element;
        }
        if (arr[i] < min_element) {
            min_element = arr[i];
        }
    }
    return max_diff;
}

int main() {
    int arr[] = {1, 2, 90, 10, 110};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("Maximum difference is %d", find_max_difference(arr, size));
    return 0;
}