#include <stdio.h>
#include <stdlib.h>

int* removeOdd(int* arr, int size, int* newSize) {
    int* newArr = (int*)malloc(size * sizeof(int));
    int j = 0;
    for(int i = 0; i < size; i++) {
        if(arr[i] % 2 == 0) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'newArr' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            newArr[j] = arr[i];
            j++;
        }
    }
    *newSize = j;
    return newArr;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    int newSize = 0;
    int* newArr = removeOdd(arr, size, &newSize);
    for(int i = 0; i < newSize; i++) {
        printf("%d ", newArr[i]);
    }
    free(newArr);
    return 0;
}