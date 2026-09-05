#include <stdio.h>
#include <stdlib.h>

int sumOddLengthSubarrays(const int *arr, int arrSize) {
    int total = 0;
    for (int i = 0; i < arrSize; i++) {
        int current_sum = 0;
        for (int j = i; j < arrSize; j++) {
            current_sum += arr[j];
            if ((j - i + 1) % 2 == 1) {
                total += current_sum;
            }
        }
    }
    return total;
}

int main(void) {
    int arr[] = {1, 4, 2, 5, 3};
    int arrSize = (int)(sizeof(arr) / sizeof(arr[0]));
    int result = sumOddLengthSubarrays(arr, arrSize);
    printf("%d\n", result);
    return 0;
}