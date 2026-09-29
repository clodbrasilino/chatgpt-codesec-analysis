#include <stdio.h>

void updateGap(int *gap) {
    *gap = (*gap * 10) / 13;

    if (*gap < 1) {
        *gap = 1;
    }
}

void combSort(int* array, int arraySize) {
    int gap = arraySize;
    int swapped = 1;

    while(gap != 1 || swapped == 1) {
        updateGap(&gap);

        swapped = 0;

        for(int i = 0; i < arraySize - gap; i++) {
            if(array[i] > array[i + gap]){
                int temp = array[i];
                array[i] = array[i + gap];
                array[i + gap] = temp;

                swapped = 1;
            }
        }
    }
}

void printArray(int* array, int arraySize) {
    for(int i = 0; i < arraySize; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");
}

int main() {
    int array[10] = {1, 5, 4, 2, 8, 6, 3, 7, 10, 9};
    combSort(array, 10);
    printArray(array, 10);

    return 0;
}