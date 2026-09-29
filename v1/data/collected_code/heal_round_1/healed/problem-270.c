#include<stdio.h>

int findSumOfEvenNumbers(const int arr[], int size) {
    int sum = 0;

    for (int i = 1; i < size; i += 2) {
        if (arr[i] % 2 == 0) {
            sum += arr[i];
        }
    }
  
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    int sum = findSumOfEvenNumbers(arr, size);
    printf("Sum of even numbers at even positions: %d\n", sum);
    return 0;
}