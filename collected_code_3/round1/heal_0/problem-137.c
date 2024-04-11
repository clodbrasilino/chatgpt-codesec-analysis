#include <stdio.h>

double findZeroRatio(int arr[], int size) {
    int i, zeroCount = 0;
    for(i = 0; i < size; i++) {
        if(arr[i] == 0) {
            zeroCount++;
        }
    }
    return (double)zeroCount / size;
}

int main() {
    int arr[] = {0, 1, 2, 0, 3, 0, 4, 5, 0};
    int size = sizeof(arr) / sizeof(arr[0]);
    double ratio = findZeroRatio(arr, size);
    printf("Ratio of zeroes: %.2f\n", ratio);
    return 0;
}