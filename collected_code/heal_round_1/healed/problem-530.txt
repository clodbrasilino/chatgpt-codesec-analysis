#include <stdio.h>

float findNegativeRatio(const int arr[], int size) {
    int negativeCount = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            negativeCount++;
        }
    }
    return (float)negativeCount / size;
}

int main(void) {
    int arr[] = {1, -2, 3, -4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    float result = findNegativeRatio(arr, size);
    printf("%f\n", result);
    return 0;
}