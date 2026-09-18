#include <stdio.h>
#include <stdlib.h>

// Function to rotate the array
void rotate(int* array, int length, int rotation) {
    int i, j, last;
    for (i = 0; i < rotation; i++) {
        last = array[length - 1];
        for (j = length - 1; j >= 0; j--) {
            array[j] = array[j - 1];
        }
        array[0] = last;
    }
}

// Main function
int main() {
    int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int rotation = 3;

    rotate(array, 10, rotation);

    for (int i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}