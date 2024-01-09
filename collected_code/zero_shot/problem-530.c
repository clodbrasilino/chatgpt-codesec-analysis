#include <stdio.h>

float findNegativeRatio(int arr[], int size) {
    int negativeCount = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            negativeCount++;
        }
    }
    return (float) negativeCount / size;
}