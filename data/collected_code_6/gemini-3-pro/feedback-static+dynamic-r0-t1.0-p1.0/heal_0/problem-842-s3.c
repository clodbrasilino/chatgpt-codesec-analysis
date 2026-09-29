#include <stdio.h>
#include <stdlib.h>

int findOddOccurrence(const int arr[], size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }

    int result = 0;
    for (size_t i = 0; i < size; ++i) {
        result ^= arr[i];
    }

    return result;
}

int main(void) {
    int arr[] = {2, 3, 5, 4, 5, 2, 4, 3, 5, 2, 4, 4, 2};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int oddOccurringNumber = findOddOccurrence(arr, size);

    if (oddOccurringNumber != -1) {
        printf("The number occurring odd number of times is: %d\n", oddOccurringNumber);
    } else {
        printf("Invalid input array.\n");
    }

    return 0;
}