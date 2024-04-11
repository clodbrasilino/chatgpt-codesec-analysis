#include <stdio.h>

int sumRange(int* arr, int start, int end) {
    int sum = 0;
    for(int i = start; i <= end; i++) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int start = 2;
    int end = 6;
    int sum = sumRange(arr, start, end);
    printf("Sum of numbers in the range %d to %d is %d\n", start, end, sum);
    return 0;
}