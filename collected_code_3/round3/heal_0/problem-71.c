#include <stdio.h>
#include <stdbool.h>

void combSort(int *array, int size) {
    int gap = size;
    bool swapped = true;

    while (gap > 1 || swapped) {
        if (gap > 1) {
            gap = (gap * 10) / 13;
        }

        swapped = false;

        for (int i = 0; gap + i < size; ++i) {
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
    int array[] = {10, 3, 2, 1, 9, 7, 8, 6, 5, 4};
    int size = sizeof(array) / sizeof(array[0]);

    combSort(array, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}