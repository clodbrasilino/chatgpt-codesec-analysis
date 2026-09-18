#include <stdio.h>
#include <limits.h>

#define ARRAY_MAX_SIZE 100

int findDiff(int arr[], int n) {
    int freq[ARRAY_MAX_SIZE] = {0};
    for(int i = 0; i < n; i++)
        freq[arr[i]]++;
    int max = INT_MIN, min = INT_MAX;
    for(int i = 0; i < ARRAY_MAX_SIZE; i++) {
        if(freq[i]) {
            if(freq[i] < min)
                min = freq[i];
            if(freq[i] > max)
                max = freq[i];
        }
    }
    return max - min;
}

int main() {
    int arr[] = {1, 2, 2, 3, 3, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("The difference is %d", findDiff(arr, n));
    return 0;
}