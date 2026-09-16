#include <stdio.h>
#include <stddef.h>

int sequential_search(const int *arr, size_t size, int key, size_t *index)
{
    size_t i;

    if (arr == NULL || index == NULL) {
        return -1;
    }

    for (i = 0; i < size; i++) {
        if (arr[i] == key) {
            *index = i;
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    int arr[] = {14, 7, 92, 3, 58, 21, 66, 39, 80, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int key = 58;
    size_t index = 0;
    int result;

    result = sequential_search(arr, size, key, &index);

    if (result == 0) {
        if (printf("Element %d found at index %zu\n", key, index) < 0) {
            return 1;
        }
    } else if (result == 1) {
        if (printf("Element %d not found in the array\n", key) < 0) {
            return 1;
        }
    } else {
        if (fprintf(stderr, "Invalid arguments passed to search function\n") < 0) {
            return 1;
        }
        return 1;
    }

    return 0;
}