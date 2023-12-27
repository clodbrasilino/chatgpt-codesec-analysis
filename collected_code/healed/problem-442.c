#include <stdio.h>

float findPositiveRatio(const int arr[], int size) {
    int positiveCount = 0;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            positiveCount++;
        }
    }
    
    return (float)positiveCount / size;
}

int main() {
    int arr[] = {3, -2, 5, -9, 0, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    float ratio = findPositiveRatio(arr, size);
    printf("Ratio of positive numbers: %.2f\n", ratio);
    
    return 0;
}