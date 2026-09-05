#include <stdio.h>
#include <stdlib.h>

int sumOddLengthSubarrays(const int* arr, int arrSize) {
    int sum = 0;
    for (int i = 0; i < arrSize; i++) {
        int left = i + 1;
        int right = arrSize - i;
        int left_even = (left + 1) / 2;
        int left_odd = left / 2;
        int right_even = (right + 1) / 2;
        int right_odd = right / 2;
        sum += arr[i] * (left_even * right_even + left_odd * right_odd);
    }
    return sum;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        return 1;
    }
    int arrSize = argc - 1;
    int* arr = (int*)malloc(arrSize * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (int i = 0; i < arrSize; i++) {
        long val = strtol(argv[i + 1], NULL, 10);
        if (val > 2147483647 || val < -2147483648) {
            free(arr);
            return 1;
        }
        arr[i] = (int)val;
    }
    int result = sumOddLengthSubarrays(arr, arrSize);
    printf("%d\n", result);
    free(arr);
    return 0;
}