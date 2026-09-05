#include <stdio.h>

int find_largest_positive(const int arr[], size_t size, int *result) {
    if (arr == NULL || result == NULL || size == 0) {
        return 0;
    }

    int largest = 0;
    int found = 0;

    for (size_t i = 0; i < size; i++) {
        if (arr[i] > 0) {
            if (!found || arr[i] > largest) {
                largest = arr[i];
                found = 1;
            }
        }
    }

    if (!found) {
        return 0;
    }

    *result = largest;
    return 1;
}

int main(void) {
    int numbers[] = {3, -1, 7, 0, -5, 2};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int largest;

    if (find_largest_positive(numbers, size, &largest)) {
        printf("Largest positive number: %d\n", largest);
    } else {
        printf("No positive numbers found.\n");
    }

    return 0;
}