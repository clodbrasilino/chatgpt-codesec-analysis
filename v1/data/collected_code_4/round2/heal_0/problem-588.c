#include <stdio.h>
#include <limits.h>

int findDifference(int arr[], int n) {
    int minElement = INT_MAX;
    int maxElement = INT_MIN;

    for (int i = 0; i < n; i++) {
        if (arr[i] < minElement) {
            minElement = arr[i];
        }
        if (arr[i] > maxElement) {
            maxElement = arr[i];
        }
    }

    return maxElement - minElement;
}

int main() {
    int arr[] = {2, 3, 1, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    int diff = findDifference(arr, n);
    printf("Difference: %d", diff);
    
    return 0;
}