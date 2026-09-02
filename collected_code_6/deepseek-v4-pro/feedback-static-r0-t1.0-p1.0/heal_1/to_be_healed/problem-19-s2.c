#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int contains_duplicate(int *arr, int size) {
    if (arr == NULL || size <= 1) {
        return 0;
    }
    
    int *sorted = (int *)malloc(size * sizeof(int));
    if (sorted == NULL) {
        return -1;
    }
    
    for (int i = 0; i < size; i++) {
        sorted[i] = arr[i];
    }
    
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (sorted[j] > sorted[j + 1]) {
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    
    for (int i = 0; i < size - 1; i++) {
        if (sorted[i] == sorted[i + 1]) {
            free(sorted);
            return 1;
        }
    }
    
    free(sorted);
    return 0;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 2, 3, 4};
    int arr3[] = {5};
    int arr4[] = {3, 1, 4, 1, 5, 9, 2, 6};
    
    printf("Array 1 has duplicates: %d\n", contains_duplicate(arr1, 5));
    printf("Array 2 has duplicates: %d\n", contains_duplicate(arr2, 5));
    printf("Array 3 has duplicates: %d\n", contains_duplicate(arr3, 1));
    printf("Array 4 has duplicates: %d\n", contains_duplicate(arr4, 8));
    printf("NULL array has duplicates: %d\n", contains_duplicate(NULL, 3));
    
    return 0;
}