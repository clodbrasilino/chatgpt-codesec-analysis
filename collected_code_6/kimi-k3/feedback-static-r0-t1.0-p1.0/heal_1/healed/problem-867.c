#include <stdio.h>

int findMinNumberToMakeEvenSum(const int arr[], int size) {
    if (arr == NULL || size <= 0) {
        return -1;
    }

    long long sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }

    if (sum % 2 == 0) {
        return 0;
    } else {
        return 1;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    int result = findMinNumberToMakeEvenSum(arr, size);

    if (result != -1) {
        printf("Minimum number to add: %d\n", result);
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}