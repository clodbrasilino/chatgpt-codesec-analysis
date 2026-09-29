#include <stdio.h>

int sum_range(int *arr, int start, int end) {
    if (arr == NULL || start < 0 || end < 0 || start > end) return -1;
    int sum = 0;
    for (int i = start; i <= end; i++) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int start = 4;
    int end = 7;
    int result = sum_range(arr, start, end);
    if (result == -1) {
        printf("Failed to calculate sum.\n");
    } else {
        printf("The sum is %d.\n", result);
    }
    return 0;
}