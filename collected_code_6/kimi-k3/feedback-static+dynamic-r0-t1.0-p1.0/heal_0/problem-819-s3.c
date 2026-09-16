#include <stdio.h>
#include <stdlib.h>

void countConsecutiveDuplicates(int arr[], int size) {
    if (size <= 0) {
        printf("Array is empty.\n");
        return;
    }

    int count = 1;
    for (int i = 1; i < size; i++) {
        if (arr[i] == arr[i - 1]) {
            count++;
        } else {
            printf("%d appears %d times\n", arr[i - 1], count);
            count = 1;
        }
    }
    printf("%d appears %d times\n", arr[size - 1], count);
}

int main() {
    int arr[] = {1, 1, 2, 2, 2, 3, 4, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    countConsecutiveDuplicates(arr, size);

    return 0;
}