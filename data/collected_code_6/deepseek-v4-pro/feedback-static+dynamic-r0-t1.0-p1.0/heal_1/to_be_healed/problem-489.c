#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int frequency_of_largest(int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return 0;
    }
    
    int largest = arr[0];
    int frequency = 1;
    
    for (int i = 1; i < size; i++) {
        if (arr[i] > largest) {
            largest = arr[i];
            frequency = 1;
        } else if (arr[i] == largest) {
            frequency++;
        }
    }
    
    return frequency;
}

int main(void) {
    int arr1[] = {1, 3, 5, 7, 7, 5, 3, 7};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("Frequency of largest in arr1: %d\n", frequency_of_largest(arr1, size1));
    
    int arr2[] = {10, 10, 10, 10};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("Frequency of largest in arr2: %d\n", frequency_of_largest(arr2, size2));
    
    int arr3[] = {42};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("Frequency of largest in arr3: %d\n", frequency_of_largest(arr3, size3));
    
    int arr4[] = {-5, -2, -8, -2, -1, -2};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("Frequency of largest in arr4: %d\n", frequency_of_largest(arr4, size4));
    
    printf("Frequency of largest with NULL: %d\n", frequency_of_largest(NULL, 5));
    printf("Frequency of largest with zero size: %d\n", frequency_of_largest(arr1, 0));
    
    return 0;
}