#include <stdio.h>

int sumOfRange(int arr[], int start, int end) {
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
    int sum = sumOfRange(arr, start, end);
    printf("Sum of elements from index %d to %d is %d\n", start, end, sum);
    return 0;
}