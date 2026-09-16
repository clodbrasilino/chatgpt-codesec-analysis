#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int sumOddLengthSubarrays(int* arr, int n) {
    int total = 0;
    
    for (int i = 0; i < n; i++) {
        int start = n - i;
        int end = i + 1;
        int total_subarrays = start * end;
        int odd_subarrays = (total_subarrays + 1) / 2;
        total += arr[i] * odd_subarrays;
    }
    
    return total;
}

int main(void) {
    int arr1[] = {1, 4, 2, 5, 3};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", sumOddLengthSubarrays(arr1, n1));
    
    int arr2[] = {1, 2};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", sumOddLengthSubarrays(arr2, n2));
    
    int arr3[] = {10, 11, 12};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", sumOddLengthSubarrays(arr3, n3));
    
    return 0;
}