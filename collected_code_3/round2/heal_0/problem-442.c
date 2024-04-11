#include <stdio.h>

double findPositiveRatio(int arr[], int size) {
    int positiveCount = 0;
    for(int i = 0; i < size; i++) {
        if(arr[i] > 0) {
            positiveCount++;
        }
    }
    return (double)positiveCount / size;
}

int main() {
    int arr[] = {1, -2, 3, -4, 5, -6, 7, -8, 9, -10};
    int size = sizeof(arr) / sizeof(arr[0]);
    double ratio = findPositiveRatio(arr, size);
    printf("The ratio of positive numbers is: %.2f\n", ratio);
    return 0;
}