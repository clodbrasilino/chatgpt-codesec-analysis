#include <stdio.h>

int minSwaps(int arr[], int n) {
    int noOfOnes = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            noOfOnes++;
        }
    }
    int maxOnes = 0;
    for (int i = 0; i < noOfOnes; i++) {
        if (arr[i] == 1) {
            maxOnes++;
        }
    }
    int tempOnes = maxOnes;
    for (int i = noOfOnes; i < n; i++) {
        if (arr[i - noOfOnes] == 1) {
            tempOnes--;
        }
        if (arr[i] == 1) {
            tempOnes++;
        }
        if (tempOnes > maxOnes) {
            maxOnes = tempOnes;
        }
    }
    return (noOfOnes - maxOnes);
}

int main() {
    int arr[] = {1, 0, 1, 0, 1, 0, 0, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d", minSwaps(arr, n));
    return 0;
}