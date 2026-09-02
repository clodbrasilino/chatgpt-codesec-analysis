#include <stdio.h>
#include <limits.h>

int findMaxFrequency(int *arr, int n) {
    int max = INT_MIN;
    for (int i = 0; i < n; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    int frequency = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] == max) {
            ++frequency;
        }
    }

    return frequency;
}

int main() {
    int arr[] = {1, 2, 3, 3, 4, 4, 4, 5, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int frequency = findMaxFrequency(arr, n);
    printf("Frequency of the largest value: %d\n", frequency);
    return 0;
}