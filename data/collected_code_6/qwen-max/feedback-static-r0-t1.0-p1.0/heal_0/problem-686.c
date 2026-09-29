#include <stdio.h>
#include <stdlib.h>

void countFrequencies(int *array, int size) {
    int *frequency = (int *)calloc(size, sizeof(int));
    for (int i = 0; i < size; ++i) {
        frequency[array[i]]++;
    }
    for (int i = 0; i < size; ++i) {
        if (frequency[i] > 0) {
            printf("Element %d: %d times\n", i, frequency[i]);
        }
    }
    free(frequency);
}

int main() {
    int array[] = {1, 2, 3, 2, 1, 2, 3, 1, 1, 4};
    int size = sizeof(array) / sizeof(array[0]);
    countFrequencies(array, 5);
    return 0;
}