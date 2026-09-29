#include <stdio.h>

float findZeroRatio(const int arr[], int size) {
    int zeroes = 0;
    for (int i = 0; i < size; i++) {
        if (0 == arr[i]) {
            zeroes++;
        }
    }
    return (float)zeroes / size;
}

int main() {
    int arr[] = {0, 2, 3, 0, 5, 0, 7, 8, 0};
    int size = sizeof(arr) / sizeof(arr[0]);

    float ratio = findZeroRatio(arr, size);
    printf("Zero Ratio: %.2f\n", ratio);

    return 0;
}