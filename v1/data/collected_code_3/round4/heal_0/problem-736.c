#include <stdio.h>

int left_insertion_point(int arr[], int n, int key) {
    int start = 0;
    int end = n - 1;
    int mid;

    while (start < end) {
        mid = start + (end - start) / 2;
        if (arr[mid] < key)
            start = mid + 1;
        else
            end = mid;
    }

    return start;
}

int main() {
    int arr[] = {1, 2, 4, 4, 8, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 4;

    int index = left_insertion_point(arr, n, key);

    printf("Left insertion point for %d is at index %d\n", key, index);

    return 0;
}