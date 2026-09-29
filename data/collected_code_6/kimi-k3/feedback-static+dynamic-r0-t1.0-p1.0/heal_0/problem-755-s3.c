#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

bool find_second_smallest(const int *arr, size_t size, int *result)
{
    size_t i;
    int smallest;
    int second_smallest;

    if (arr == NULL || result == NULL || size < 2U) {
        return false;
    }

    smallest = INT_MAX;
    second_smallest = INT_MAX;

    for (i = 0U; i < size; i++) {
        if (arr[i] < smallest) {
            second_smallest = smallest;
            smallest = arr[i];
        } else if (arr[i] < second_smallest && arr[i] != smallest) {
            second_smallest = arr[i];
        }
    }

    if (second_smallest == INT_MAX) {
        return false;
    }

    *result = second_smallest;
    return true;
}

int main(void)
{
    int arr[] = {12, 13, 1, 10, 34, 1};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result;

    if (find_second_smallest(arr, size, &result)) {
        printf("Second smallest element: %d\n", result);
    } else {
        printf("Could not determine the second smallest element.\n");
    }

    return 0;
}