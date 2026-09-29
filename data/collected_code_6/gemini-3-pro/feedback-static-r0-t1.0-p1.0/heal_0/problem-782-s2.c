#include <stdio.h>
#include <stdlib.h>

int sumOddLengthSubarrays(int* arr, int arrSize) {
    if (arr == NULL || arrSize <= 0) {
        return 0;
    }

    int totalSum = 0;

    for (int i = 0; i < arrSize; i++) {
        int leftPaths = i + 1;
        int rightPaths = arrSize - i;
        int totalPaths = leftPaths * rightPaths;
        int oddPaths = (totalPaths + 1) / 2;
        
        totalSum += oddPaths * arr[i];
    }

    return totalSum;
}

int main(void) {
    int arr[] = {1, 4, 2, 5, 3};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    int result = sumOddLengthSubarrays(arr, arrSize);
    printf("%d\n", result);

    return 0;
}