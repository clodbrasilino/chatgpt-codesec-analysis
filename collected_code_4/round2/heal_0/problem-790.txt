#include <stdio.h>
#include <stdbool.h>

bool checkEvenIndexEvenNumbers(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        if (i % 2 == 0 && arr[i] % 2 != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr[] = {2, 1, 4, 7, 6};
    int size = sizeof(arr) / sizeof(arr[0]);
    if (checkEvenIndexEvenNumbers(arr, size)) {
        printf("Even indexed elements are even.\n");
    } else {
        printf("Even indexed elements are not even.\n");
    }
    return 0;
}