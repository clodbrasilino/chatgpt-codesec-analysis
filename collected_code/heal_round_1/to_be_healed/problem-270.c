#include<stdio.h>

int findSumOfEvenNumbers(int arr[], int size) {
    int sum = 0;
  
    // iterate over the array starting from the second element with even index
    for (int i = 1; i < size; i += 2) {
      
        // check if the current number is even
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] % 2 == 0) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
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