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
    int arr[] = {1, 0, 3, 0, 5, 0, 7, 0, 9, 0};
    int size = sizeof(arr) / sizeof(arr[0]);
    double ratio = findZeroRatio(arr, size);
    printf("Ratio of zeroes in array: %.2f\n", ratio);
    return 0;
}