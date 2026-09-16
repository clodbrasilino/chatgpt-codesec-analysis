#include <stdio.h>

int minSwaps(const int arr[], int n) {
    int onesCount = 0;
    int swapCount = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            onesCount++;
        }
    }
    
    int currentOnes = 0;
    for (int i = 0; i < onesCount; i++) {
        if (arr[i] == 1) {
            currentOnes++;
        }
    }
    
    int maxOnes = currentOnes;
    for (int i = onesCount; i < n; i++) {
        if (arr[i - onesCount] == 1) {
            currentOnes--;
        }
        if (arr[i] == 1) {
            currentOnes++;
        }
        if (currentOnes > maxOnes) {
            maxOnes = currentOnes;
        }
    }
    
    swapCount = onesCount - maxOnes;
    
    int zerosCount = n - onesCount;
    int currentZeros = 0;
    for (int i = 0; i < zerosCount; i++) {
        if (arr[i] == 0) {
            currentZeros++;
        }
    }
    
    int maxZeros = currentZeros;
    for (int i = zerosCount; i < n; i++) {
        if (arr[i - zerosCount] == 0) {
            currentZeros--;
        }
        if (arr[i] == 0) {
            currentZeros++;
        }
        if (currentZeros > maxZeros) {
            maxZeros = currentZeros;
        }
    }
    
    int swapCountZeros = zerosCount - maxZeros;
    
    return swapCount < swapCountZeros ? swapCount : swapCountZeros;
}

int main(void) {
    int arr1[] = {0, 0, 1, 0, 1, 0, 1, 1};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", minSwaps(arr1, n1));
    
    int arr2[] = {1, 0, 1, 0, 1};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", minSwaps(arr2, n2));
    
    int arr3[] = {1, 1, 1, 1, 0, 0, 0, 0};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", minSwaps(arr3, n3));
    
    int arr4[] = {0, 1, 0, 1, 0, 1};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%d\n", minSwaps(arr4, n4));
    
    return 0;
}