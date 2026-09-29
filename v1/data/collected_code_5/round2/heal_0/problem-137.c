#include <stdio.h>

double getZeroRatio(int *array, int size) {
    if (array == NULL || size == 0) {
        return 0.0;
    }
    
    int zeroCount = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] == 0) {
            zeroCount++;
        }
    }

    return (double)zeroCount / size;
}

int main() {
    int array[10] = {1, 0, 2, 0, 3, 4, 0, 0, 5, 6};
    printf("Zero ratio is: %f\n", getZeroRatio(array, 10));

    return 0;
}