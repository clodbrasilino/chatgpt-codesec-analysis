#include <stdio.h>

int findLargestFrequency(int arr[], int n) {
    int max = arr[0], maxCount = 0;
    for (int i = 0; i < n; ++i) {
        int count = 0;
        for (int j = 0; j < n; ++j) {
            if (arr[j] == arr[i])
                ++count;
        }
        if (count > maxCount) {
            maxCount = count;
            max = arr[i];
        } else if (count == maxCount) {
            if (arr[i] > max)
                max = arr[i];
        }
    }
    return maxCount;
}

int main() {
    int arr[] = {1, 2, 2, 3, 3, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Frequency of Largest element: %d\n", findLargestFrequency(arr, n));
    return 0;
}