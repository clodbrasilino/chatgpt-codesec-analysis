#include <stdio.h>

int oddOccurrence(const int arr[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= arr[i];
    }
    return result;
}

int main() {
    int arr[] = {1, 2, 3, 2, 1, 3, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    int oddNumber = oddOccurrence(arr, size);

    printf("Number which occurs odd number of times: %d\n", oddNumber);

    return 0;
}