#include <stdio.h>
#include <limits.h>

int findSmallest(int arr[], int n) {
    int i;
    int min = INT_MAX;

    for (i = 0; i < n; i++)
        if (arr[i] < min)
            min = arr[i];

    return min;
}

int main() {
    int arr[] = {12, 1234, 45, 67, 1};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Smallest number in the array is %d", findSmallest(arr, n));
    return 0;
}