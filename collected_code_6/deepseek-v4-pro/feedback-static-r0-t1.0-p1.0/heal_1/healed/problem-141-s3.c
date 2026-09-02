#include <stdio.h>
#include <stdlib.h>

void flip(int arr[], int i) {
    int start = 0;
    while (start < i) {
        int temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
        start++;
        i--;
    }
}

int find_max_index(const int arr[], int n) {
    int max_idx = 0;
    for (int i = 1; i < n; ++i) {
        if (arr[i] > arr[max_idx]) {
            max_idx = i;
        }
    }
    return max_idx;
}

void pancake_sort(int arr[], int n) {
    for (int curr_size = n; curr_size > 1; --curr_size) {
        int max_idx = find_max_index(arr, curr_size);
        if (max_idx != curr_size - 1) {
            if (max_idx != 0) {
                flip(arr, max_idx);
            }
            flip(arr, curr_size - 1);
        }
    }
}

int main(void) {
    int arr[] = {23, 10, 20, 11, 12, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    pancake_sort(arr, n);

    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}