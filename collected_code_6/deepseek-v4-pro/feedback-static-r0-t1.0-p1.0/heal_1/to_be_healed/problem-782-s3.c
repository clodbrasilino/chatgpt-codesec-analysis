#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int sumOddLengthSubarrays(int* arr, int arrSize) {
    int totalSum = 0;
    
    for (int i = 0; i < arrSize; i++) {
        int startChoices = i + 1;
        int endChoices = arrSize - i;
        int totalSubarrays = startChoices * endChoices;
        int oddSubarrays = (totalSubarrays + 1) / 2;
        
        totalSum += arr[i] * oddSubarrays;
    }
    
    return totalSum;
}

int main(void) {
    int arr1[] = {1, 4, 2, 5, 3};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = sumOddLengthSubarrays(arr1, size1);
    printf("%d\n", result1);
    
    int arr2[] = {1, 2};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = sumOddLengthSubarrays(arr2, size2);
    printf("%d\n", result2);
    
    int arr3[] = {10, 11, 12};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    int result3 = sumOddLengthSubarrays(arr3, size3);
    printf("%d\n", result3);
    
    return EXIT_SUCCESS;
}