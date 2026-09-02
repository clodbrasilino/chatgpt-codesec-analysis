#include <stdio.h>
#include <stdbool.h>

bool isUnique(const int *arr, int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == value) {
            return false;
        }
    }
    return true;
}

int sumOfNonRepeatedElements(const int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        if (isUnique(arr, i, arr[i])) {
            sum += arr[i];
        }
    }
    return sum;
}

int main() {
    const int arr[] = {1, 2, 3, 4, 5, 1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = sumOfNonRepeatedElements(arr, n);
    printf("Sum of non-repeated elements: %d\n", result);

    return 0;
}