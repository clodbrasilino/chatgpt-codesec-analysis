#include <stdio.h>
#include <stdlib.h>

int minSwaps(const int arr[], int n) {
    int count_ones = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            count_ones++;
        }
    }

    int max_ones = 0, ones_in_window = 0;
    for (int i = 0; i < count_ones; i++) {
        if (arr[i] == 1) {
            ones_in_window++;
        }
    }

    max_ones = ones_in_window;

    for (int i = count_ones; i < n; i++) {
        if (arr[i] == 1) {
            ones_in_window++;
        }
        if (arr[i - count_ones] == 1) {
            ones_in_window--;
        }
        if (max_ones < ones_in_window) {
            max_ones = ones_in_window;
        }
    }

    return count_ones - max_ones;
}

int main() {
    const int arr[] = {1, 0, 1, 0, 1, 0, 0, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Minimum swaps required: %d\n", minSwaps(arr, n));
    return 0;
}