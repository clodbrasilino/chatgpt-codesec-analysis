#include <stdio.h>
#include <stdlib.h>

int findMinDifference(int arr[], int n) {
    int minDiff = abs(arr[0] - arr[1]);
    
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (abs(arr[i] - arr[j]) < minDiff) {
                minDiff = abs(arr[i] - arr[j]);
            }
        }
    }

    return minDiff;
}

int main() {
    int arr[] = {2, 5, 10, 12, 15, 21};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    int minDiff = findMinDifference(arr, n);

    printf("Minimum difference is %d\n", minDiff);
    
    return 0;
}