#include <stdio.h>
#include <stdbool.h>

void combSort(int *array, int size) {
    int gap = size;
    bool swapped = true;

    while (gap > 1 || swapped == true) {
        gap = (gap * 10) / 13;
        if (gap < 1) {
            gap = 1;
        }

        swapped = false;

        for (int i = 0; i < size - gap; i++) {
            if (array[i] > array[i + gap]) {
                int temp = array[i];
                array[i] = array[i + gap];
                array[i + gap] = temp;

                swapped = true;
            }
        }
    }
}

int main() {
    int array[] = {20, 40, 50, 10, 30};
    int size = sizeof(array) / sizeof(array[0]);

    combSort(array, size);

    printf("Sorted array: \n");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}