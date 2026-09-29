#include <stdio.h>
#include <limits.h>

int find_difference(const int arr[], int size) {
    if (size <= 0) {
        return -1;
    }
    int min = INT_MAX;
    int max = INT_MIN;
    for (int i = 0; i < size; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    return max - min;
}

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    int diff = find_difference(arr, size);
    if (diff != -1) {
        printf("%d\n", diff);
    }
    return 0;
}