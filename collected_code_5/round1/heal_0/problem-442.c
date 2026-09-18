#include <stdio.h>

double findPositiveRatio(int* arr, int size) {
    int i, positive_count = 0;

    if(arr == NULL || size <= 0) {
        return 0.0;
    }

    for(i = 0; i < size; i++) {
        if(arr[i] > 0) {
            positive_count++;
        }
    }

    return (double)positive_count / size;
}

int main() {
    int arr[] = {10, -20, 30, -40, 50};

    printf("The ratio of positive numbers is %.2f\n", findPositiveRatio(arr, 5));

    return 0;
}