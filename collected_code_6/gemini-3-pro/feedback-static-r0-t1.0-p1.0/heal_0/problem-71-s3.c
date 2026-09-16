#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

void comb_sort(int *array, size_t size) {
    if (array == NULL || size <= 1) {
        return;
    }

    size_t gap = size;
    bool swapped = true;

    while (gap > 1 || swapped) {
        gap = (gap * 10) / 13;
        
        if (gap < 1) {
            gap = 1;
        }

        swapped = false;

        for (size_t i = 0; i < size - gap; i++) {
            if (array[i] > array[i + gap]) {
                int temp = array[i];
                array[i] = array[i + gap];
                array[i + gap] = temp;
                swapped = true;
            }
        }
    }
}

void print_array(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return;
    }
    
    for (size_t i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main(void) {
    int data[] = {8, 4, 1, 56, 3, -44, 23, -6, 28, 0};
    size_t size = sizeof(data) / sizeof(data[0]);

    comb_sort(data, size);
    print_array(data, size);

    return 0;
}