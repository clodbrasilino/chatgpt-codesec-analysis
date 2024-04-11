#include <stdio.h>
#include <limits.h>

#define MAX_SIZE 1000

int findDifference(int arr[], int n) {
    int freq[MAX_SIZE] = {0};
    int i, max, min;

    for(i = 0; i < n; i++) {
        freq[arr[i]]++;
    }

    max = min = freq[0];
    for(i = 0; i < MAX_SIZE; i++) {
        if(freq[i] > max) {
            max = freq[i];
        }
        if(freq[i] != 0 && freq[i] < min) {
            min = freq[i];
        }
    }

    return max - min;
}

int main() {
    int arr[] = {1, 2, 2, 1, 1, 2, 3, 3, 3, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Difference = %d", findDifference(arr, n));

    return 0;
}