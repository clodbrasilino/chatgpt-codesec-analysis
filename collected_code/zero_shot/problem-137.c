#include <stdio.h>

float findZeroRatio(int arr[], int size) {
    int zeroes = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == 0) {
            zeroes++;
        }
    }
    return (float)zeroes / size;
}