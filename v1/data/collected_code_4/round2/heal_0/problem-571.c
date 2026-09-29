#include <stdio.h>
#include <stdlib.h>

int maxPairSum(int *arr, int size, int k){
    int i, j, maxSum = 0, sum;

    for(i = 0; i < size; i++) {
        for(j = i+1; j < size; j++) {
            sum = arr[i] + arr[j];
            if(sum < k && sum > maxSum){
                maxSum = sum;
            }
        }
    }

    return maxSum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int k = 7;

    int result = maxPairSum(arr, size, k);
    printf("Max Pair Sum: %d", result);
  
    return 0;
}