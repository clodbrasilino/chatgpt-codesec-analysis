#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minDiff(int arr[], int n) {
    int diff = INT_MAX;
    for (int i=0; i<n-1; i++)
        for (int j=i+1; j<n; j++)
            if (abs(arr[i] - arr[j]) < diff)
                diff = abs(arr[i] - arr[j]);
    return diff;
}

int main() {
    int arr[] = {1, 5, 3, 19, 18, 25};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Minimum difference is %d\n", minDiff(arr, n));
    return 0;
}