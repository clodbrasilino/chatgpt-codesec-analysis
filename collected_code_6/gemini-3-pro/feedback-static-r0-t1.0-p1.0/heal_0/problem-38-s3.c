#include <stdio.h>
#include <stdlib.h>

int findFirstEven(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            return arr[i];
        }
    }
    return 0;
}

int findFirstOdd(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            return arr[i];
        }
    }
    return 0;
}

double divideFirstEvenAndOdd(int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return 0.0;
    }

    int firstEven = findFirstEven(arr, size);
    int firstOdd = findFirstOdd(arr, size);

    if (firstOdd == 0) {
        return 0.0;
    }

    return (double)firstEven / (double)firstOdd;
}

int main() {
    int arr[] = {3, 5, 8, 10, 7, 2};
    int size = sizeof(arr) / sizeof(arr[0]);

    double result = divideFirstEvenAndOdd(arr, size);

    if (result != 0.0) {
        printf("%f\n", result);
    } else {
        printf("0.0\n");
    }

    return 0;
}