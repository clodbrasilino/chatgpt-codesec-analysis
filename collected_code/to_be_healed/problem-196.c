#include <stdio.h>

void removeTuples(int* array, int size, int k) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'array[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (array[i] != k) {
            /* Possible weaknesses found:
             *  Cannot determine that 'array[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            array[count] = array[i];
            count++;
        }
    }
    for (int i = count; i < size; i++) {
        array[i] = 0;
    }
}

int main() {
    int arr[] = {5, 2, 4, 3, 5, 2, 6, 7, 8};
    int size = sizeof(arr) / sizeof(arr[0]);
    int k = 2;

    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    removeTuples(arr, size, k);
    
    printf("\nModified array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    
    return 0;
}