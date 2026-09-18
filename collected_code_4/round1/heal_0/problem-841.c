#include <stdio.h>

int countInversions(int array[], int array_size) {
    int count = 0;
    int i, j;

    for (i=0; i<array_size-1; i++) {
        for (j=i+1; j<array_size; j++) {
            if (array[i] > array[j]) {
                count ++;
            }
        }
    }
    return count;
}

int main() {
    int array[] = {10, 20, 15, 30, 25};
    int array_size = sizeof(array)/sizeof(array[0]);

    int inversion_count = countInversions(array, array_size);

    printf("Number of inversions are: %d \n", inversion_count);

    return 0;
}