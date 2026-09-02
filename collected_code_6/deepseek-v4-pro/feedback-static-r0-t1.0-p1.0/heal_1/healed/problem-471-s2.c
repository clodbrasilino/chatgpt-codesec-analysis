#include <stdio.h>

int findRemainder(const int arr[], int size, int n) {
    if (size <= 0 || n == 0) {
        return -1;
    }

    long long remainder = 1;

    for (int i = 0; i < size; i++) {
        remainder = (remainder * (arr[i] % n)) % n;
    }

    return (int)remainder;
}

int main(void) {
    int arr[] = {100, 10, 5, 25, 35, 14};
    int size = sizeof(arr) / sizeof(arr[0]);
    int n = 11;

    int result = findRemainder(arr, size, n);

    if (result != -1) {
        printf("Remainder: %d\n", result);
    } else {
        printf("Invalid input\n");
    }

    return 0;
}