#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool areNumbersConsecutive(const int *arr, int n) {
    if (n <= 0) return false;

    for (int i = 0; i < n - 1; i++) {
        if (arr[i] + 1 != arr[i + 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr[] = {2, 3, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    if (areNumbersConsecutive(arr, n)) {
        printf("The list contains consecutive numbers.\n");
    } else {
        printf("The list does not contain consecutive numbers.\n");
    }

    return 0;
}