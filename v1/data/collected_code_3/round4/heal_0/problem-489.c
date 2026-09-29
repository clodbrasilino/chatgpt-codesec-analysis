#include <stdio.h>
#include <limits.h>

int findFrequency(int arr[], int n) {
    int max = INT_MIN;
    int freq = 0;
    for (int i = 0; i < n; i++) {
        if (max < arr[i]) {
            max = arr[i];
            freq = 1;
        } else if (max == arr[i]) {
            freq++;
        }
    }
    return freq;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 5, 5, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Frequency of largest value is %d\n", findFrequency(arr, n));
    return 0;
}