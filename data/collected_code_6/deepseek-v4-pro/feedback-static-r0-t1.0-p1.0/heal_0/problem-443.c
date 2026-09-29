#include <stdio.h>
#include <limits.h>

int find_largest_negative(const int *arr, size_t size, int *result) {
    if (arr == NULL || result == NULL || size == 0) {
        return 0;
    }

    int largest_negative = INT_MIN;
    int found = 0;

    for (size_t i = 0; i < size; i++) {
        if (arr[i] < 0) {
            if (!found || arr[i] > largest_negative) {
                largest_negative = arr[i];
                found = 1;
            }
        }
    }

    if (!found) {
        return 0;
    }

    *result = largest_negative;
    return 1;
}

int main(void) {
    int arr[] = {-5, -2, -10, -3, 0, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result;

    if (find_largest_negative(arr, size, &result)) {
        printf("Largest negative number: %d\n", result);
    } else {
        printf("No negative numbers found\n");
    }

    return 0;
}