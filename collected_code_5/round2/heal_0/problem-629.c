#include <stdio.h>

void findEvenNumbers(int* array, int size) {
    int i;
    for(i = 0; i < size; i++) {
        if(array[i] % 2 == 0) {
            printf("%d ", array[i]);
        }
    }
    printf("\n");
}

int main() {
    int mixedArray[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arraySize = sizeof(mixedArray) / sizeof(int);

    findEvenNumbers(mixedArray, arraySize);

    return 0;
}