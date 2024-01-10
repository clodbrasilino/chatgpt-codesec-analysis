#include <stdio.h>

void countConsecutiveDuplicates(const int arr[], int size) {
    int count = 0;

    for (int i = 1; i < size; i++) {
        if (arr[i] == arr[i - 1]) {
            count++;
        }
    }

    printf("Frequency of consecutive duplicate elements: %d\n", count);
}

int main() {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    int size = sizeof(arr) / sizeof(arr[0]);

    countConsecutiveDuplicates(arr, size);

    return 0;
}