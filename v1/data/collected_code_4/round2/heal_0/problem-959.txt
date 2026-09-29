#include <stdio.h>

double average(int* arr, int size) {
    if (arr == NULL || size <= 0) {
        printf("Invalid inputs.\n");
        return 0;
    }

    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }

    return sum / size;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    double avg = average(arr, size);

    printf("The average is %lg\n", avg);

    return 0;
}