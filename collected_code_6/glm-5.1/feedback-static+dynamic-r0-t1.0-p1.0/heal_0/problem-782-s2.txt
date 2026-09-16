#include <stdio.h>
#include <stdlib.h>

int sumOddLengthSubarrays(int *arr, int arrSize) {
    int total = 0;
    if (arr == NULL || arrSize <= 0) {
        return 0;
    }
    for (int i = 0; i < arrSize; i++) {
        int left = i + 1;
        int right = arrSize - i;
        int left_even = left / 2;
        int right_even = right / 2;
        int left_odd = (left + 1) / 2;
        int right_odd = (right + 1) / 2;
        total += arr[i] * (left_even * right_even + left_odd * right_odd);
    }
    return total;
}

int main() {
    int arrSize;
    if (scanf("%d", &arrSize) != 1 || arrSize <= 0) {
        return 1;
    }
    int *arr = (int *)malloc(arrSize * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (int i = 0; i < arrSize; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }
    int result = sumOddLengthSubarrays(arr, arrSize);
    printf("%d\n", result);
    free(arr);
    return 0;
}