#include <stdio.h>
#include <stdlib.h>

void power_elements(int *array, int size, int n) {
    for (int i = 0; i < size; ++i) {
        int result = 1;
        for (int j = 0; j < n; ++j) {
            result *= array[i];
        }
        array[i] = result;
    }
}

int main() {
    int array[] = {2, 3, 4, 5};
    int size = sizeof(array) / sizeof(array[0]);
    int n = 3;

    power_elements(array, size, n);

    for (int i = 0; i < size; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}