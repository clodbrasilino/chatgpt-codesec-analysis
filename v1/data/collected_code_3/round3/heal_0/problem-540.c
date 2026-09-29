#include <stdio.h>
#include <limits.h>

#define SIZE 100

int findDifference(int arr[], int n) {
    int freq[SIZE] = {0};
    int i, max = INT_MIN, min = INT_MAX;

    for(i = 0; i < n; i++) {
        freq[arr[i]]++;
    }

    for(i = 0; i < SIZE; i++) {
        if(freq[i]) {
            if(freq[i] > max) {
                max = freq[i];
            }
            if(freq[i] < min) {
                min = freq[i];
            }
        }
    }

    return max - min;
}

int main() {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("%d", findDifference(arr, n));
    return 0;
}