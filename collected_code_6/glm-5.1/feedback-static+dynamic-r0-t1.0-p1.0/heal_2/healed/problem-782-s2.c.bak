#include <stdio.h>
#include <stdlib.h>

long long sumOddLengthSubarrays(const int *arr, int arrSize) {
    long long total = 0;
    if (arr == NULL || arrSize <= 0) {
        return 0;
    }
    for (int i = 0; i < arrSize; i++) {
        long long left = i + 1;
        long long right = arrSize - i;
        long long left_even = left / 2;
        long long right_even = right / 2;
        long long left_odd = (left + 1) / 2;
        long long right_odd = (right + 1) / 2;
        total += (long long)arr[i] * (left_even * right_even + left_odd * right_odd);
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
    long long result = sumOddLengthSubarrays(arr, arrSize);
    printf("%lld\n", result);
    free(arr);
    return 0;
}