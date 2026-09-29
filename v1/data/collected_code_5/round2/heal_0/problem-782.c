#include <stdio.h>

int sumOddLengthSubarrays(int* arr, int arrSize){
    int sum = 0;
    for (int length = 1; length <= arrSize; length+=2) {
        for (int start = 0; start + length - 1 < arrSize; start++) {
            for (int i = start; i < start+length; i++) {
                if (i < arrSize) {
                    sum += arr[i];
                }
            }
        }
    }
    return sum;
}
 
int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    int result = sumOddLengthSubarrays(arr, arrSize);

    printf("Sum of all odd length subarrays is %d", result);
    
    return 0;
}