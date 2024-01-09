#include<stdio.h>

int findSumOfEvenNumbers(int arr[], int size) {
    int sum = 0;
  
    // iterate over the array starting from the second element with even index
    for (int i = 1; i < size; i += 2) {
      
        // check if the current number is even
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